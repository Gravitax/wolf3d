/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/11/25 18:03:46 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void     init_sdl(t_wolf *data)
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1) 
        clean_exit(data, "wolf3d: SDL_Init fail", 0);
	if (TTF_Init() == -1)
	{
    	printf("Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
	    exit(EXIT_FAILURE);
	}
    data->sdl_on = 1;
    data->pWindow = SDL_CreateWindow("maboye wolf3d",
		SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
		W_WIDTH, W_HEIGHT, 0);
	if (!(data->police = TTF_OpenFont("img/police/AmazDooMLeft.ttf", 200)) || !(data->police2 = TTF_OpenFont("img/police/8-BIT\ WONDER.ttf", 30)) || !(data->police3 = TTF_OpenFont("img/police/8-BIT\ WONDER.ttf", 10)))
	{
		printf("TTF_OpenFont: %s\n", TTF_GetError());
	    exit(EXIT_FAILURE);
	}

}

static void     get_fps(t_wolf *data)
{
    float       pframe;
    
    pframe = clock();
    data->etime = (pframe / CLOCKS_PER_SEC)
        - (data->frame_start / CLOCKS_PER_SEC);
    data->fps =  (int)(1 / data->etime);
    if (data->etime > 0.016)
        SDL_Delay(data->etime * 1000 - 16);
    //printf("fps: %d\n", data->fps);
}

static void		launch_game(t_wolf *data)
{
    init_sdl(data);
    if (data->pWindow) 
    { 
        if (!(data->renderer = SDL_CreateRenderer(data->pWindow, -1, 0)))
            clean_exit(data, "wolf3d: SDL_CreateRenderer fail", 0);
        load_datagame(data);
		while (1)
		{
            data->frame_start = clock();
			events(data);
            display(data);
            get_fps(data);
            SDL_RenderPresent(data->renderer);
            SDL_DestroyTexture(data->window);
		}
    }
    else
        clean_exit(data, "wolf3d: SDL_CreateWindow fail", 0);
}

void			wolf3d(t_wolf *data)
{
    data->map.len = data->map.height * data->map.width;
	data->map.depth = data->map.width > data->map.height
		? data->map.width : data->map.height;
	data->player.y = data->player.pos / data->map.width;
	data->player.x = data->player.pos - (data->player.y * data->map.width) + 1;
	data->player.angle = 0;
    data->player.fov = 3.14159 / 4;
    data->player.ms = 0.6;
	data->player.speed = 12;
    data->player.health = 200;
    data->player.health_max = 200;
    data->player.weapon = 0;
    data->raydata.ray_step = 0.01;
	data->map.sc_x = 2;
	launch_game(data);

}
