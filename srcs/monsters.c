/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monsters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:30:54 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void     remove_deadmobs(t_wolf *data)
{
    t_object   *tmp;
    t_object   *head;

    if (data->monster == NULL)
        return ;
    head = data->monster;
    while (data->monster && data->monster->dead == 1)
    {
        tmp = data->monster->next;
        ft_memdel((void **)&data->monster);
        data->monster = tmp;
        head = data->monster;
    }
    while (data->monster)
    {
        tmp = data->monster;
        data->monster = data->monster->next;
        while (data->monster && data->monster->dead == 1)
        {
            tmp->next = data->monster->next;
            ft_memdel((void **)&data->monster);
            data->monster = tmp->next;
        }
    }
    data->monster = head;
}

static void     smoothness(t_wolf *data, t_node *current)
{
    float   tmpx;
    float   tmpy;

    if (distance(data->monster->x, data->monster->y,
    current->x, current->y) > data->map.depth)
        return ;
    tmpx = (current->x + 0.5f - data->monster->x)
        * data->etime * data->monster->speed;
    tmpy = (current->y + 0.5f - data->monster->y)
        * data->etime * data->monster->speed;
    data->monster->x += tmpx;
    data->monster->y += tmpy;
    if (data->monster->x < 0 || data->monster->x > data->map.width
    || data->monster->y < 0 || data->monster->y > data->map.height
    || data->map.map[(int)data->monster->x
        + data->map.width * (int)data->monster->y] == 1)
    {
        data->monster->x -= tmpx;
        data->monster->y -= tmpy;
    }
}

static void     monster_moves(t_wolf *data)
{
    t_node  *current;

    current = data->pfdata.end;
    while (current->parent)
    {
        if (current->parent == data->pfdata.start)
            break ;
        current = current->parent;
    }
    data->pfdata.list[(int)data->monster->x
        + data->map.width * (int)data->monster->y].bobstacle = 0;
    smoothness(data, current);
    data->pfdata.list[(int)data->monster->x
        + data->map.width * (int)data->monster->y].bobstacle = 1;
}

static void     monster_actions(t_wolf *data)
{
    float   dst;

    data->pfdata.start = &data->pfdata.list[(int)data->monster->x
        + data->map.width * (int)data->monster->y];
    data->pfdata.end = &data->pfdata.list[(int)data->player.x
        + data->map.width * (int)data->player.y];
     dst = distance(data->monster->x, data->monster->y,
        data->pfdata.end->x, data->pfdata.end->y);
    if (dst > 2)
    {
        data->monster->si = data->monster->type;
        if ((dst < 15 || data->monster->hp < data->monster->si * 20)
        && (data->monster->delay-- < 1))
        {
            astar(data);
            monster_moves(data);
            data->monster->delay = data->monster->si + 10;
        }
    }
    else
    {
        data->monster->si = data->monster->type + 7;
        data->player.health -= data->monster->type * 2;
        data->monster->delay = data->monster->si * 10;
        if (data->player.health < 1)
        {
            printf("score: %d\n", data->kill_score);
            //clean_exit(data, NULL, 1);
        }
    }
}

static void     spawner(t_wolf *data)
{
    int         monsters;
    t_object    *newmonster;

    monsters = lst_len(data->monster) - 1;
    if (monsters < 10)
        data->monster->delay = data->monster->si * 20;
    else if (monsters < 20)
        data->monster->delay = data->monster->si * 40;
    else
    {
        data->monster->delay = data->monster->si * 100;
        return ;
    }
    newmonster = (t_object *)ft_memalloc(sizeof(t_object));
    newmonster->x = data->monster->x;
    newmonster->y = data->monster->y;
    int     skin;

    skin = 7;
    if (data->kill_score > 10)
        skin = 8;
    if (data->kill_score > 20)
        skin = 9;
    newmonster->type = skin;
    newmonster->si = skin;
    newmonster->delay = newmonster->si * 10;
    newmonster->hp = newmonster->si * 20;
    newmonster->sprite = data->sprite[7];
    newmonster->speed = newmonster->si + data->kill_score;
    if (newmonster->speed > 30)
        newmonster->speed = 30;
    lst_pushback(data->monster, newmonster);
    if (data->monster == NULL)
        clean_exit(data, "wolf3d: malloc error", 0);
}

void            monsters(t_wolf *data)
{
    t_object    *head;

    remove_deadmobs(data);
    head = data->monster;
    while (data->monster)
    {
        if (data->monster->type > 5 && data->monster->type < 10)
        {
            if (data->monster->delay-- < 0)
            {
                if (data->monster->type == 6)
                    spawner(data);
                else
                    monster_actions(data);
            }
        }
        data->monster = data->monster->next;
    }
    data->monster = head;
    objects(data, data->monster);
}
