/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/11/05 17:14:32 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void     get_weapondata(t_wolf *data)
{
    int             i;
    int             si;
    SDL_Surface     *weapon;

    if (data->kill_score > 10)
        data->player.weapon = 1;
    if (data->kill_score > 20)
        data->player.weapon = 2;
    if (data->kill_score > 30)
        data->player.weapon = 3;
    i = data->player.weapon;
    si = data->player.wdata[i].si;
    weapon = data->sprite[si].img;
    data->player.wdata[i].zpixel
        = get_pixel(data, si, 0, 0);
    data->player.wdata[i].height = W_HEIGHT / 3;
    data->player.wdata[i].ratio = (float)weapon->h / (float)weapon->w;
    data->player.wdata[i].width
        = data->player.wdata[i].height / data->player.wdata[i].ratio;
    if (data->player.weapon == 0)
        data->player.wdata[i].column
            = (data->player.wdata[i].height / 2 - 35);
    else
        data->player.wdata[i].column = 0;
}

void            weapons(t_wolf *data)
{
    int             i;
    int             x;
    int             y;
    uint32_t        pixel;

    i = data->player.weapon;
    get_weapondata(data);
    x = -1;
    while (++x < data->player.wdata[i].width)
    {
        y = -1;
        while (++y < data->player.wdata[i].height)
        {
            pixel = get_pixel(data, data->player.wdata[i].si,
                x / data->player.wdata[i].width,
                y / data->player.wdata[i].height);
            if (pixel == data->player.wdata[i].zpixel)
                continue ;
            put_pixel(data->screen,
                (W_WIDTH / 2) - data->player.wdata[i].column + x,
                (W_HEIGHT - data->player.wdata[i].height) + y, pixel);
        }
    }
}
