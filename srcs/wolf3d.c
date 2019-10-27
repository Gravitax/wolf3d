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

static void     load_texture(t_wolf *data)
{
	if (!(data->surface[0].img = SDL_LoadBMP("img/doom.bmp")))
        clean_exit(data, "wolf3d: sdl loadbmp error: wolf3d.c 1", 0);
    if (!(data->surface[1].img = SDL_LoadBMP("img/brick.bmp")))
        clean_exit(data, "wolf3d: sdl loadbmp error: wolf3d.c 2", 0);
    if (!(data->surface[2].img = SDL_LoadBMP("img/rock.bmp")))
        clean_exit(data, "wolf3d: sdl loadbmp error: wolf3d.c 3", 0);
    if (!(data->surface[3].img = SDL_LoadBMP("img/stone.bmp")))
        clean_exit(data, "wolf3d: sdl loadbmp error: wolf3d.c 4", 0);
    if (!(data->surface[4].img = SDL_LoadBMP("img/wood.bmp")))
        clean_exit(data, "wolf3d: sdl loadbmp error: wolf3d.c 5", 0);
    if (!(data->surface[5].img = SDL_LoadBMP("img/grass.bmp")))
        clean_exit(data, "wolf3d: sdl loadbmp error: wolf3d.c 6", 0);
    if (!(data->surface[6].img = SDL_LoadBMP("img/sand.bmp")))
        clean_exit(data, "wolf3d: sdl loadbmp error: wolf3d.c 7", 0);
    if (!(data->surface[7].img = SDL_LoadBMP("img/night.bmp")))
        clean_exit(data, "wolf3d: sdl loadbmp error: wolf3d.c 8", 0);
    data->bgf = SDL_CreateTextureFromSurface(data->renderer, data->surface[6].img);
    data->bgc = SDL_CreateTextureFromSurface(data->renderer, data->surface[7].img);
}

static void     get_fps(t_wolf *data)
{
    float       pframe;
    
    pframe = clock();
    data->etime = (pframe / CLOCKS_PER_SEC) - (data->frame_start / CLOCKS_PER_SEC);
    data->fps =  (int)(1 / data->etime);
    if (data->fps < 10 || data->fps > 240)
        clean_exit(data,"wolf3d: unexpected frame rate", 0);
    printf("fps: %d\n", data->fps);
}

static void     draw_background(t_wolf *data)
{
    SDL_Rect    rect;

    rect.w = W_WIDTH;
    rect.h = W_HEIGHT / 2;
    rect.x = 0;
    rect.y = 0;
    SDL_RenderCopy(data->renderer, data->bgc, NULL, &rect);
    rect.y = W_HEIGHT / 2;
    SDL_RenderCopy(data->renderer, data->bgf, NULL, &rect);
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
            data->frame_start = clock();
            SDL_RenderClear(data->renderer);
            draw_background(data);
			sdl_event(data);
            //raythread(data);
            raycasting(data);
            //minimap(data);
            get_fps(data);
            SDL_RenderPresent(data->renderer);
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
	data->player.speed = 5;
    data->raydata.ray_step = 0.01;
	launch_game(data);
}
