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
        clean_exit(data, "wolf3d: sdl init error: wolf3d.c", 0);
    data->sdl_on = 1;
    data->pWindow = SDL_CreateWindow("maboye wolf3d",
		SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
		W_WIDTH, W_HEIGHT, 0);
}

static void     get_fps(t_wolf *data)
{
    float       pframe;
    
    pframe = clock();
    data->etime = (pframe / CLOCKS_PER_SEC) - (data->frame_start / CLOCKS_PER_SEC);
    data->fps =  (int)(1 / data->etime);
    printf("fps: %d\n", data->fps);
}

static void		launch_game(t_wolf *data)
{
    init_sdl(data);
    if (data->pWindow) 
    { 
        if (!(data->renderer = SDL_CreateRenderer(data->pWindow, -1, 0)))
            clean_exit(data, "wolf3d: sdl renderer error: wolf3d.c", 0);
        load_surface_andtexture(data);
		while (1)
		{
            data->frame_start = clock();
			sdl_event(data);
            display(data);
            get_fps(data);
            SDL_RenderPresent(data->renderer);
            SDL_DestroyTexture(data->window);
		}
        SDL_DestroyRenderer(data->renderer);
		SDL_DestroyWindow(data->pWindow);
        SDL_Quit();
    }
    else
        clean_exit(data, "wolf3d: sdl window error: wolf3d.c", 0);
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

	data->player.y = data->player.pos / data->map.width;
	data->player.x = data->player.pos - (data->player.y * data->map.width) + 1;
	data->player.angle = 0;
    data->player.fov = 3.14159 / 4;
    data->player.ms = 0.6;
	data->player.speed = 1;
    data->raydata.ray_step = 0.01;
	launch_game(data);
}
