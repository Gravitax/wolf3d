/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 01:04:10 by saneveu           #+#    #+#             */
/*   Updated: 2019/12/14 01:06:47 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void            draw_wall(t_wolf *d, int x)
{
    int y;
    int dis;

    if (d->ray.wallside == 0)
        d->ray.wallx = d->player.y + d->ray.perpWallDist * d->ray.diry;
    else
        d->ray.wallx = d->player.x + d->ray.perpWallDist * d->ray.dirx;
    d->map.depth_buffer[x] = d->ray.perpWallDist;
    d->ray.wallx = d->ray.wallx - (int)d->ray.wallx;
    d->ray.wtx = (int)(d->ray.wallx * (double)d->sprite[d->ray.tex].img->w);
    if ((d->ray.wallside == 0 && d->ray.dirx > 0)
        || (d->ray.wallside == 1 && d->ray.diry < 0))
        d->ray.wtx = d->sprite[d->ray.tex].img->w - d->ray.wtx;
    y = d->ray.walltop;
    while (y < d->ray.wallbot)
    {
        dis = y * 256 - W_HEIGHT * 128 + d->ray.height * 128;
        d->ray.wty = ((dis * d->sprite[d->ray.tex].img->h) / d->ray.height) / 256;
        put_pixel(d->screen, x, y, get_pixel_ray(d, d->ray.tex, d->ray.wtx, d->ray.wty));
		y++;
    }
}

void            get_tex(t_wolf *d)
{
    if (!(d->ray.wallside) && d->ray.dirx < 0)
        d->ray.tex = 16;
    else if (!(d->ray.wallside) && d->ray.dirx >= 0)
        d->ray.tex = 17;
    else if (d->ray.wallside && d->ray.diry < 0)
        d->ray.tex = 18;
    else if (d->ray.wallside && d->ray.diry >= 0)
        d->ray.tex = 19;
}

