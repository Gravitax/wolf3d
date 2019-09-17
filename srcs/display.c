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

static void     draw_rect(t_wolf *data, int i, int j, int padding)
{
    SDL_Rect rect;

    rect.x = i;
    rect.y = j;
    rect.h = padding;
    rect.w = padding;
    if (SDL_RenderFillRect(data->renderer, &rect) == -1)
        clean_exit(data, "wolf3d: sdl fillrect error: init.c", 0);
}

static void     draw_map(t_wolf *data)
{
    t_bloc  *tmp;

    tmp = data->bloclist;
    while (tmp->next)
    {
        SDL_SetRenderDrawColor(data->renderer, 255, 255, 255, 100);
        if (tmp->wall)
            SDL_SetRenderDrawColor(data->renderer, 0, 0, 255, 100);
        draw_rect(data,
                data->player.x, data->player.y,
                data->player.padding);
        draw_rect(data,
            tmp->x, tmp->y,
            data->map.padding);
        tmp = tmp->next;
    }
    SDL_RenderPresent(data->renderer);
    return ;
}

void            display_game(t_wolf *data)
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1) 
        clean_exit(data, "wolf3d: sdl init error: init.c", 0);
    data->sdl_token = 1;
    data->pWindow = SDL_CreateWindow("maboye wolf3d",
		SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
		W_WIDTH, W_HEIGTH, 0);
    if (data->pWindow) 
    { 
        if (!(data->renderer = SDL_CreateRenderer(data->pWindow, -1, 0)))
            clean_exit(data, "wolf3d: sdl renderer error: init.c", 0);
		while (1)
		{
			handle_sdl_event(data);
            draw_map(data);
		}
        SDL_DestroyRenderer(data->renderer);
		SDL_DestroyWindow(data->pWindow);
    } 
    else
        clean_exit(data, "wolf3d: sdl window error: init.c", 0);
    SDL_Quit();
}
