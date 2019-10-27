/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:05:22 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:08:19 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			draw_pixel(t_wolf *data, int surface_index)
{
	int			sx;
	int			sy;
	uint8_t		*p;
	t_surface	surface;

	surface = data->surface[surface_index];
	SDL_LockSurface(surface.img);
	sx = data->raydata.samplex * surface.img->w;
	sy = data->raydata.sampley * surface.img->h;
	p = (uint8_t *)surface.img->pixels + sy * surface.img->pitch
		+ sx * surface.img->format->BytesPerPixel;
	SDL_UnlockSurface(surface.img);
	SDL_SetRenderDrawColor(data->renderer, p[2], p[1], p[0], 100);
}

static void		draw_ray(t_wolf *data, int x)
{
	int	y;

	data->raydata.ceiling = W_HEIGHT / 2 - W_HEIGHT / data->raydata.dst_towall;
	data->raydata.floor = W_HEIGHT - data->raydata.ceiling;
	y = data->raydata.ceiling;
    while (++y < W_HEIGHT)
	{
		if (y <= data->raydata.floor && data->raydata.dst_towall < data->map.depth)
		{
			SDL_SetRenderDrawColor(data->renderer, 0, 0, 100, 100);
			// data->raydata.sampley = ((float)y - (float)data->raydata.ceiling)
			// 	/ ((float)data->raydata.floor - (float)data->raydata.ceiling);
			// draw_pixel(data, data->si);
		}
		else if (y > data->raydata.floor)
		{
			break ;
			float b = (((float)y - W_HEIGHT / 2) / ((float)W_HEIGHT / 2));
			SDL_SetRenderDrawColor(data->renderer, 200 * b, 200 * b, 200 * b, 100);
		}
		else
			continue ;
		SDL_RenderDrawPoint(data->renderer, x, y);
	}
}

static int		hitwall(t_wolf *data)
{
	int	testx;
	int	testy;
	
	testx = (int)(data->player.x
		+ data->raydata.eyex * data->raydata.dst_towall);
	testy = (int)(data->player.y
		+ data->raydata.eyey * data->raydata.dst_towall);
	if (testx < 0 || testx >= data->map.width
	|| testy < 0 || testy >= data->map.height)
	{
		data->raydata.dst_towall = data->map.depth;
		return (1);
	}
	else if (data->map.map[testy * data->map.width + testx] == 1)
	{
		//get_blockside(data, testx, testy);
		return (1);
	}
	else
		return (0);
}

void			raycasting(t_wolf *data)
{
	int	x;

	x = -1;
	while (++x < W_WIDTH)
	{
		data->raydata.angle = (data->player.angle - data->player.fov / 2)
			+ ((float)x / (float)W_WIDTH) * data->player.fov;
		data->raydata.dst_towall = 0;
		data->raydata.eyex = cosf(data->raydata.angle);
		data->raydata.eyey = sinf(data->raydata.angle);
		while (data->raydata.dst_towall < data->map.depth)
		{
			if (hitwall(data) == 1)
				break ;
			data->raydata.dst_towall += data->raydata.ray_step;
		}
		draw_ray(data, x);
	}
	SDL_SetRenderDrawColor(data->renderer, 100, 0, 0, 100);
}
