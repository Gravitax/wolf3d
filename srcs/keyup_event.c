/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyup_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:30:54 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static int      get_bloc(t_wolf *data, int x, int y)
{
    int xc;
    int yc;

    if (y < 0 || y > data->map.height * data->map.padding
            || x < 0 || x > data->map.width * data->map.padding)
        return (-1);
    xc = -1;
    while (x > 0)
    {
        x -= data->map.padding;
        ++xc;
    }
    yc = -1;
    while (y > 0)
    {
        y -= data->map.padding;
        ++yc;
    }
    return (inblock(data, xc, yc));
}

static void     check_playeraccess(t_wolf *data, int xs, int ys)
{
    int x;
    int y;
    int i;

    i = data->player.padding;
    y = data->player.y;
    x = data->player.x;
    x -= data->map.start;
    if (get_bloc(data, x, y) || get_bloc(data, x + i, y)
        || get_bloc(data, x, y + i) || get_bloc(data, x + i, y + i))
    {
        data->player.x = xs;
        data->player.y = ys;
    }
}

void            keyup_event(t_wolf *data)
{
    int xs = data->player.x;
    int ys = data->player.y;

    if (data->event.key.keysym.sym == SDLK_UP)
        data->player.y -= 2 + data->player.speed;
    else if (data->event.key.keysym.sym == SDLK_DOWN)
        data->player.y += 2 + data->player.speed;
    else if (data->event.key.keysym.sym == SDLK_LEFT)
        data->player.x -= 2 + data->player.speed;
    else if (data->event.key.keysym.sym == SDLK_RIGHT)
        data->player.x += 2 + data->player.speed;
    else if (data->event.key.keysym.sym == SDLK_LSHIFT)
        data->player.speed = 0;
    check_playeraccess(data, xs, ys);
}
