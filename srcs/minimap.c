/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:30:54 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void     draw_minimap(t_wolf *data, SDL_Rect rect, int nx, int px)
{
    int ny;
    int py;

    ny = -1;
    py = 0;
    while (++ny < data->map.height)
	{
		if (data->map.map[ny * data->map.width + nx] == 1)
			SDL_SetRenderDrawColor(data->renderer, 0, 0, 255, 100);
		else if ((ny + 1) * data->map.width + nx == data->player.pos)
			SDL_SetRenderDrawColor(data->renderer, 255, 0, 100, 100);
		else
			SDL_SetRenderDrawColor(data->renderer, 255, 255, 255, 100);
		rect.x = nx + px;
		rect.y = ny + py;
		rect.h = 10;
		rect.w = 10;
		SDL_RenderFillRect(data->renderer, &rect);
		py += 10;
    }
}

void        minimap(t_wolf *data)
{
    int nx;
    int px;
	SDL_Rect rect;

    nx = -1;
    px = 0;
    data->player.pos = (int)data->player.x
		+ ((int)data->player.y + 1) * data->map.width;
	while (++nx < data->map.width)
	{
		draw_minimap(data, rect, nx, px);
		px += 10;
	}
}
