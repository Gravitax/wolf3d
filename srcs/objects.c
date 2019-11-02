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

static void     get_objdata(t_wolf *data, t_object *list)
{
    data->objdata.ceiling = (float)(W_HEIGHT / 2)
        - W_HEIGHT / data->objdata.dst_fromplayer;
    data->objdata.floor = W_HEIGHT - data->objdata.ceiling;
    data->objdata.height = data->objdata.floor - data->objdata.ceiling;
    data->objdata.ratio = (float)list->sprite.img->h
        / (float)list->sprite.img->w;
    data->objdata.width = data->objdata.height / data->objdata.ratio;
    data->objdata.mid = (0.5 * (data->objdata.angle
        / (data->player.fov / 2)) + 0.5) * W_WIDTH;
}

static void     get_objangle(t_wolf *data, t_object *list)
{
    data->objdata.vecx = list->x - data->player.x;
    data->objdata.vecy = list->y - data->player.y;
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
}

static void     put_objpixel(t_wolf *data, t_object *list, float sy)
{
    uint32_t    pixel;

    if (data->objdata.column < 0 || data->objdata.column > W_WIDTH)
        return ;
    if (data->map.depth_buffer[data->objdata.column]
    < data->objdata.dst_fromplayer)
        return ;
    pixel = get_pixel(data, list->si,
        data->objdata.samplex, data->objdata.sampley);
    if (pixel == data->objdata.zpixel)
         return ;
    put_pixel(data->screen,
        data->objdata.column,
        data->objdata.ceiling + sy,
        pixel);
    data->map.depth_buffer[data->objdata.column]
        = data->objdata.dst_fromplayer;
}

static void     display_object(t_wolf *data, t_object *list)
{
    float   sx;
    float   sy;

    data->objdata.zpixel = get_pixel(data, list->si, 0, 0);
    sx = -1;
    while (++sx < data->objdata.width)
    {
        sy = -1;
        while (++sy < data->objdata.height)
        {
            data->objdata.samplex = sx / data->objdata.width;
            data->objdata.sampley = sy / data->objdata.height;
            data->objdata.column = (int)(data->objdata.mid + sx
                - (data->objdata.width / 2));
            put_objpixel(data, list, sy);
        }
    }
}

void            objects(t_wolf *data, t_object *list)
{
    t_object    *head;

    head = list;
    if (list == NULL)
        return ;
    while (list)
    {
        if (list->type)
        {
            get_objangle(data, list);
            if (fabs(data->objdata.angle) < data->player.fov / 2
            && data->objdata.dst_fromplayer > 1
            && data->objdata.dst_fromplayer < data->map.depth)
            {
                get_objdata(data, list);
                display_object(data, list);
            }
        }
        list = list->next;
    }
    list = head;
}
