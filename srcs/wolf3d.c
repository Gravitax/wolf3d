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

void            load_texture(t_wolf *data)
{
	if (!(data->surface[0].img = SDL_LoadBMP("img/doom.bmp")))
        clean_exit(data, "wolf3d: sdl loadbmp error: wolf3d.c", 0);
    if (!(data->surface[1].img = SDL_LoadBMP("img/brick.bmp")))
        clean_exit(data, "wolf3d: sdl loadbmp error: wolf3d.c", 0);
    if (!(data->surface[2].img = SDL_LoadBMP("img/rock.bmp")))
        clean_exit(data, "wolf3d: sdl loadbmp error: wolf3d.c", 0);
    if (!(data->surface[3].img = SDL_LoadBMP("img/stone.bmp")))
        clean_exit(data, "wolf3d: sdl loadbmp error: wolf3d.c", 0);
    if (!(data->surface[4].img = SDL_LoadBMP("img/wood.bmp")))
        clean_exit(data, "wolf3d: sdl loadbmp error: wolf3d.c", 0);
}

static void		launch_game(t_wolf *data)
{
    init_sdl(data);
    if (data->pWindow) 
    { 
        if (!(data->renderer = SDL_CreateRenderer(data->pWindow, -1, 0)))
            clean_exit(data, "wolf3d: sdl renderer error: wolf3d.c", 0);
        load_texture(data);
		while (1)
		{
            SDL_RenderClear(data->renderer);
            //data->frame_start = SDL_GetTicks();
			sdl_event(data);
            raycasting(data);
            //minimap(data);
            SDL_RenderPresent(data->renderer);
            //frame_delay(SDL_GetTicks() - data->frame_start);
		}
        SDL_DestroyRenderer(data->renderer);
		SDL_DestroyWindow(data->pWindow);
    } 
    else
        clean_exit(data, "wolf3d: sdl window error: wolf3d.c", 0);
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
    data->ray_step = 0.01;
	launch_game(data);
}