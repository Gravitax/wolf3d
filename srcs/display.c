/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/10/28 16:35:15 by saneveu          ###   ########.fr       */
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

static void     minimap(t_wolf *data, SDL_Rect rect)
{
    int nx;
    int px;

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

void            display(t_wolf *data)
{
    unsigned int    *pixels;
    SDL_Rect        rect;
    int             i;

    raythread(data);
    rect.w = W_WIDTH;
    rect.h = W_HEIGHT / 2;
    rect.x = 0;
    rect.y = W_HEIGHT / 2;
    SDL_RenderCopy(data->renderer, data->bgf, NULL, &rect);
    rect.y = 0;
    SDL_RenderCopy(data->renderer, data->bgc, NULL, &rect);
    rect.h = W_HEIGHT;
    SDL_LockSurface(data->screen);
    data->window = SDL_CreateTextureFromSurface(data->renderer, data->screen);
    SDL_RenderCopy(data->renderer, data->window, NULL, &rect);
    pixels = (unsigned int *)data->screen->pixels;
    i = -1;
    while (++i < W_WIDTH * W_HEIGHT)
        pixels[i] = 0x000000;
    SDL_UnlockSurface(data->screen);
    minimap(data, rect);
}
