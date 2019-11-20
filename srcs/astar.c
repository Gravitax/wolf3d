/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:30:54 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void     resetdata(t_wolf *data)
{
    int i;

    i = -1;
    while (++i < data->map.len)
    {
        data->pfdata.list[i].bvisited = 0;
        data->pfdata.list[i].globalgoal = 1000;
        data->pfdata.list[i].localgoal = 1000;
        data->pfdata.list[i].parent = NULL;
    }
}

static void     neighbour(t_wolf *data, t_node *current, int i)
{
    float   plowergoal;
    t_node  *ngbhr;

    ngbhr = current->ngbhr[i];
    if (ngbhr->bvisited == 0 && ngbhr->bobstacle == 0 && ngbhr->wall == 0)
        alst_pushback(data->pfdata.alst, ngbhr);
    if (data->pfdata.alst == NULL)
        clean_exit(data, "wolf3d: malloc error", 0);
    plowergoal = current->localgoal
        + distance(current->x, current->y, ngbhr->x, ngbhr->y);
    if (plowergoal < ngbhr->localgoal)
    {
        ngbhr->parent = current;
        ngbhr->localgoal = plowergoal;
        ngbhr->globalgoal = ngbhr->localgoal
            + distance(ngbhr->x, ngbhr->y,
                data->pfdata.end->x, data->pfdata.end->y);
    }
}

static void     delvisited_nodes(t_wolf *data)
{    
    t_alst   *tmp;
    t_alst   *head;

    if (data->pfdata.alst == NULL)
        return ;
    head = data->pfdata.alst;
    while (data->pfdata.alst && data->pfdata.alst->node->bvisited == 1)
    {
        tmp = data->pfdata.alst->next;
        ft_memdel((void **)&data->pfdata.alst);
        data->pfdata.alst = tmp;
        head = data->pfdata.alst;
    }
    while (data->pfdata.alst)
    {
        tmp = data->pfdata.alst;
        data->pfdata.alst = data->pfdata.alst->next;
        while (data->pfdata.alst && data->pfdata.alst->node->bvisited == 1)
        {
            tmp->next = data->pfdata.alst->next;
            ft_memdel((void **)&data->pfdata.alst);
            data->pfdata.alst = tmp->next;
        }
    }
    data->pfdata.alst = head;
}

void            astar(t_wolf *data)
{
    t_node  *current;

    resetdata(data);
    current = data->pfdata.start;
    current->localgoal = 0;
    current->globalgoal = distance(data->pfdata.start->x,
        data->pfdata.start->y, data->pfdata.end->x, data->pfdata.end->y);
    if (!(data->pfdata.alst = (t_alst *)ft_memalloc(sizeof(t_alst))))
        clean_exit(data, "wolf3d: malloc error", 0);
    data->pfdata.alst->node = data->pfdata.start;
    while (current != data->pfdata.end)
    {
        alst_sort(data->pfdata.alst);
        delvisited_nodes(data);
        if (!alst_len(data->pfdata.alst))
            break ;
        current = data->pfdata.alst->node;
        current->bvisited = 1;
        neighbour(data, current, 0);
        neighbour(data, current, 1);
        neighbour(data, current, 2);
        neighbour(data, current, 3);
    }
}
