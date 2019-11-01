/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:48:08 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:10:56 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void            objects(t_wolf *data)
{
    t_object    *head;

    head = data->object;
    while (data->object)
    {
        if (data->object->type == 0)
            break ;

        data->objdata.vecx = data->object->x - data->player.x;
        data->objdata.vecy = data->object->y - data->player.y;
        data->objdata.dst_fromplayer
            = ft_sqrt(data->objdata.vecx * data->objdata.vecx
            + data->objdata.vecy * data->objdata.vecy);

        data->objdata.eyex = cosf(data->player.angle);
        data->objdata.eyey = sinf(data->player.angle);

        data->objdata.angle
            = atan2f(data->objdata.eyex, data->objdata.eyey)
            - atan2f(data->objdata.vecx, data->objdata.vecy);

        if (data->objdata.angle < -3.14159)
            data->objdata.angle += 2 * 3.14159;
        else if (data->objdata.angle > 3.14159)
            data->objdata.angle -= 2 * 3.14159;

        if (fabs(data->objdata.angle) < data->player.fov / 2)
            data->objdata.infov = 1;
        else
            data->objdata.infov = 0;

        if (data->objdata.infov && data->objdata.dst_fromplayer >= 0.5
        && data->objdata.dst_fromplayer < data->map.depth)
        {
            data->objdata.ceiling = (float)(W_HEIGHT / 2)
                - W_HEIGHT / data->objdata.dst_fromplayer;
            data->objdata.floor = W_HEIGHT - data->objdata.ceiling;
            data->objdata.height = data->objdata.floor - data->objdata.ceiling;
            data->objdata.ratio = (float)data->object->sprite.img->h
                / (float)data->object->sprite.img->w;
            data->objdata.width = data->objdata.height / data->objdata.ratio;
            data->objdata.mid = (0.5 * (data->objdata.angle
                / (data->player.fov / 2)) + 0.5) * W_WIDTH;

            for (float lx = 0; lx < data->objdata.width; lx++)
            {
                for (float ly = 0; ly < data->objdata.height; ly++)
                {
                    data->objdata.samplex = lx / data->objdata.width;
                    data->objdata.sampley = ly / data->objdata.height;

                    data->objdata.column = (int)(data->objdata.mid + lx
                        - (data->objdata.width / 2));
                    if (data->objdata.column >= 0
                    && data->objdata.column < W_WIDTH)
                    {
                        put_pixel(data->screen,
                            data->objdata.column,
                            data->objdata.ceiling + ly,
                            get_pixel(data, data->object->si,
                                data->objdata.samplex,
                                data->objdata.sampley));
                    }
                }
            }
        }
        data->object = data->object->next;
    }
    data->object = head;
}
