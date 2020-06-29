/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebosson <bebosson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/06/29 09:15:35 by bebosson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		init_sdl(t_wolf *data)
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
		clean_exit(data, "wolf3d: SDL_Init fail", 0);
	data->sdl_on = 1;
	if (!(data = minimap_alloc(data)))
		clean_exit(data, "wolf3d: error malloc minimap", 0);
	if (TTF_Init() == -1)
		clean_exit(data, "wolf3d: error TTF_init", 0);
	data->pwindow = SDL_CreateWindow("maboye wolf3d",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			W_WIDTH, W_HEIGHT, 0);
	if (!(data->police = TTF_OpenFont("img/police/AmazDooMLeft.ttf", 200)))
		clean_exit(data, "wolf3d: error TTF_OpenFont", 0);
	if (!(data->police2 = TTF_OpenFont("img/police/bit.ttf", 20)))
		clean_exit(data, "wolf3d: error TTF_OpenFont", 0);
	if (!(data->police3 = TTF_OpenFont("img/police/bit.ttf", 8)))
		clean_exit(data, "wolf3d: error TTF_OpenFont", 0);
}

static int		get_fps(t_wolf *data)
{
	int	pframe;

	pframe = 1000 / FPS;
	data->fps = 1000 / (data->frame_start - data->etime);
	if (data->frame_start - data->etime >= pframe)
	{
		data->etime = data->frame_start;
		return (1);
	}
	SDL_Delay(pframe - (data->frame_start - data->etime));
	return (0);
}

static void		launch_game(t_wolf *data)
{
	init_sdl(data);
	if (data->pwindow)
	{
		if (!(data->renderer = SDL_CreateRenderer(data->pwindow, -1, 0)))
			clean_exit(data, "wolf3d: SDL_CreateRenderer fail", 0);
		load_datagame(data);
		while (1)
		{
			data->frame_start = SDL_GetTicks();
			if (get_fps(data) == 1)
			{
				events(data);
				display(data);
			}
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
	data->player.fov = 3.14159f / 4;
	data->player.ms = 2.2f;
	data->player.ms /= 100;
	data->player.speed = 6;
	data->player.speed /= 100;
	data->player.health = 200;
	data->player.health_max = 200;
	data->player.weapon = 0;
	data->raydata.ray_step = 0.01;
	data->map.sc_x = 3;
	data->key[KP] = 1;
	launch_game(data);
}
