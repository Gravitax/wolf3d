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

static void     remove_deadmobs(t_object *list)
{    
    t_object   *tmp;
    t_object   *head;

    return ;
    if (list == NULL)
        return ;
    head = list;
    while (list && list->dead == 1)
    {
        tmp = list->next;
        ft_memdel((void **)&list);
        list = tmp;
        head = list;
    }
    while (list)
    {
        tmp = list;
        list =list->next;
        while (list && list->dead == 1)
        {
            tmp->next = list->next;
            ft_memdel((void **)&list);
            list = tmp->next;
        }
    }
    list = head;
}

static void     monster_moves(t_wolf *data)
{
    (void)data;
    return ;
}

void            monsters(t_wolf *data)
{
    t_object    *head;

    objects(data, data->monster);
    remove_deadmobs(data->monster);
    head = data->monster;
    while (data->monster)
    {
        if (data->monster->type > 6)
        {
            data->pfdata.start = &data->pfdata.list[(int)data->monster->x
                + data->map.width * (int)data->monster->y];
            data->pfdata.end = &data->pfdata.list[(int)data->player.x
                + data->map.width * (int)data->player.y];
            astar(data);
            monster_moves(data);
        }
        data->monster = data->monster->next;
    }
    data->monster = head;
}
