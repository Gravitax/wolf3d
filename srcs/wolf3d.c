/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:30:54 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void     init_sdl(t_wolf *data)
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1) 
        clean_exit(data, "wolf3d: sdl init error: launcher.c", 0);
    data->sdl_token = 1;
    data->pWindow = SDL_CreateWindow("maboye wolf3d",
		SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
		W_WIDTH, W_HEIGTH, 0);
}

static void		launch_game(t_wolf *data)
{
    init_sdl(data);
    if (data->pWindow) 
    { 
        if (!(data->renderer = SDL_CreateRenderer(data->pWindow, -1, 0)))
            clean_exit(data, "wolf3d: sdl renderer error: launcher.c", 0);
		while (1)
		{
            SDL_RenderClear(data->renderer);
            data->frame_start = SDL_GetTicks();
			sdl_event(data);
            raycasting(data);
            minimap(data);
            frame_delay(SDL_GetTicks() - data->frame_start);
            SDL_RenderPresent(data->renderer);
		}
        SDL_DestroyRenderer(data->renderer);
		SDL_DestroyWindow(data->pWindow);
    } 
    else
        clean_exit(data, "wolf3d: sdl window error: launcher.c", 0);
    SDL_Quit();
}

void			wolf3d(t_wolf *data)
{
    data->map.len = data->map.height * data->map.width;
	data->map.depth = data->map.width > data->map.height
		? data->map.width : data->map.height;

	for (int i = 0; i < data->map.len; i++)
	{
		if (i > 0 && i % data->map.width == 0)
			ft_putchar('\n');
        if (i == data->player.pos)
            ft_putstr("\033[31mX\033[0m");
        else
		    ft_putnbr(data->map.map[i]);
	}
	ft_putchar('\n');

	data->player.x = 8;
	data->player.y = 8;
	data->player.speed = 0.1;
	data->player.angle = 0;
	launch_game(data);
}
