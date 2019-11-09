/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:30:54 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void     get_neighbourpos(t_wolf *data)
{
    int     x;
    int     y;

    x = -1;
    while (++x < data->map.width)
    {
        y = -1;
        while (++y < data->map.height)
        {
            if (y > 0)
                data->pfdata.list[x + y * data->map.width].ngbhr[0]
                    = &data->pfdata.list[(y - 1) * data->map.width + (x + 0)];
            if (y < data->map.height - 1)
                data->pfdata.list[x + y * data->map.width].ngbhr[1]
                    = &data->pfdata.list[(y + 1) * data->map.width + (x + 0)];
            if (x > 0)
                data->pfdata.list[x + y * data->map.width].ngbhr[2]
                    = &data->pfdata.list[(y + 0) * data->map.width + (x - 1)];
            if (x < data->map.width - 1)
                data->pfdata.list[x + y * data->map.width].ngbhr[3]
                    = &data->pfdata.list[(y + 0) * data->map.width + (x + 1)];
        }
    }
}

void            get_nodes(t_wolf *data)
{
    int     i;
    int     x;
    int     y;

    if (!(data->pfdata.list = (t_node *)ft_memalloc(sizeof(t_node)
    * (data->map.height * data->map.width))))
        clean_exit(data, "malloc error", 0);
    i = 0;
    x = -1;
    while (++x < data->map.width)
    {
        y = -1;
        while (++y < data->map.height)
        {
            data->pfdata.list[i].i = i;
            ++i;
            data->pfdata.list[y * data->map.width + x].x = x;
            data->pfdata.list[y * data->map.width + x].y = y;
            if (data->map.map[y * data->map.width + x] == 1)
            {
                data->pfdata.list[y * data->map.width + x].bobstacle = 1;
                data->pfdata.list[y * data->map.width + x].wall = 1;
            }
        }
    }
    get_neighbourpos(data);
}
