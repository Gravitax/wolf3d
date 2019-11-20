/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:48:08 by maboye            #+#    #+#             */
/*   Updated: 2019/11/05 13:21:04 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void     get_objdata(t_wolf *data, t_object *list)
{
    list->data.ceiling = (float)(W_HEIGHT / 2)
        - W_HEIGHT / list->data.dst_fromplayer;
    list->data.floor = W_HEIGHT - list->data.ceiling;
    list->data.height = list->data.floor - list->data.ceiling;
    list->data.ratio = (float)list->sprite.img->h
        / (float)list->sprite.img->w;
    list->data.width = list->data.height / list->data.ratio;
    list->data.mid = (0.5 * (list->data.angle
        / (data->player.fov / 2)) + 0.5) * W_WIDTH;
}

static void     get_objangle(t_wolf *data, t_object *list)
{
    float   vecx;
    float   vecy;

    vecx = list->x - data->player.x;
    vecy = list->y - data->player.y;
    list->data.dst_fromplayer
        = ft_sqrt(vecx * vecx + vecy * vecy);
    //    = Q_sqrt(vecx * vecx + vecy * vecy);
    list->data.eyex = cosf(data->player.angle);
    list->data.eyey = sinf(data->player.angle);
    list->data.angle = atan2f(list->data.eyex, list->data.eyey)
        - atan2f(vecx, vecy);
    if (list->data.angle < -3.14159)
        list->data.angle += 2 * 3.14159;
    else if (list->data.angle > 3.14159)
        list->data.angle -= 2 * 3.14159;
}

static void     put_objpixel(t_wolf *data, t_object *list, float sy)
{
    uint32_t    pixel;

    if (list->data.column < 0 || list->data.column > W_WIDTH)
        return ;
    if (data->map.depth_buffer[list->data.column]
    < list->data.dst_fromplayer)
        return ;
    pixel = get_pixel(data, list->si,
        list->data.samplex, list->data.sampley);
    if (pixel == list->data.zpixel)
        return ;
    put_pixel(data->screen,
        list->data.column,
        list->data.ceiling + sy, pixel);
    data->map.depth_buffer[list->data.column]
        = list->data.dst_fromplayer;
}

static void     display_object(t_wolf *data, t_object *list)
{
    float   sx;
    float   sy;

    list->data.zpixel = get_pixel(data, list->si, 0, 0);
    sx = -1;
    while (++sx < list->data.width)
    {
        sy = -1;
        while (++sy < list->data.height)
        {
            list->data.samplex = sx / list->data.width;
            list->data.sampley = sy / list->data.height;
            list->data.column = (int)(list->data.mid + sx
                - (list->data.width / 2));
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
        if (list->type > 2 && list->type < 10)
        {
            get_objangle(data, list);
            if (fabs(list->data.angle) < data->player.fov / 2
            && list->data.dst_fromplayer > 1
            && list->data.dst_fromplayer < data->map.depth)
            {
                get_objdata(data, list);
                display_object(data, list);
            }
        }
        list = list->next;
    }
    list = head;
}
