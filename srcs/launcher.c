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

void            launch_game(t_wolf *data)
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1) 
        clean_exit(data, "wolf3d: sdl init error: launcher.c", 0);
    data->sdl_token = 1;
    data->pWindow = SDL_CreateWindow("maboye wolf3d",
		SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
		W_WIDTH, W_HEIGTH, 0);
    if (data->pWindow) 
    { 
        if (!(data->renderer = SDL_CreateRenderer(data->pWindow, -1, 0)))
            clean_exit(data, "wolf3d: sdl renderer error: launcher.c", 0);
		while (1)
		{
            data->frame_start = SDL_GetTicks();
			sdl_event(data);
            //raycasting(data);
            draw_map(data);
            frame_delay(SDL_GetTicks() - data->frame_start);
		}
        SDL_DestroyRenderer(data->renderer);
		SDL_DestroyWindow(data->pWindow);
    } 
    else
        clean_exit(data, "wolf3d: sdl window error: launcher.c", 0);
    SDL_Quit();
}
