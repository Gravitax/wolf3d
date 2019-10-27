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

static void		draw_point(t_wolf *data, int x, int y, unsigned int color)
{
	unsigned int	*pixels;
	
	if (x < 0 || x > W_WIDTH || y < 0 || y > W_HEIGHT)
		return ;
	SDL_LockSurface(data->screen);
	pixels = (unsigned int *)data->screen->pixels;
	pixels[x + (y * W_WIDTH)] = color;
	SDL_UnlockSurface(data->screen);
}

static void		draw_pixel(t_wolf *data, int sprite_index, int x, int y)
{
	int			sx;
	int			sy;
	uint8_t		*p;
	uint32_t	pixels;
	t_sprite	surface;

	if (x < 0 || x > W_WIDTH || y < 0 || y > W_HEIGHT)
		return ;
	surface = data->sprite[sprite_index];
	SDL_LockSurface(surface.img);
	sx = data->raydata.samplex * surface.img->w;
	sy = data->raydata.sampley * surface.img->h;
	p = (uint8_t *)surface.img->pixels + sy * surface.img->pitch
		+ sx * surface.img->format->BytesPerPixel;
	pixels = (p[2] | p[1] << 8 | p[0] << 16 | 255 << 24);
	SDL_UnlockSurface(surface.img);
	draw_point(data, x, y, pixels);
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
			data->raydata.sampley = ((float)y - (float)data->raydata.ceiling)
				/ ((float)data->raydata.floor - (float)data->raydata.ceiling);
			draw_pixel(data, data->si, x, y);
		}
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
		get_blockside(data, testx, testy);
		return (1);
	}
	else
		return (0);
}

void			*raycasting(void *d)
{
	t_wolf	*data;

	data = (t_wolf *)d;
	while (data->x < data->x_max)
	{
		data->raydata.angle = (data->player.angle - data->player.fov / 2)
			+ ((float)data->x / (float)W_WIDTH) * data->player.fov;
		data->raydata.dst_towall = 0;
		data->raydata.eyex = cosf(data->raydata.angle);
		data->raydata.eyey = sinf(data->raydata.angle);
		while (data->raydata.dst_towall < data->map.depth)
		{
			if (hitwall(data) == 1)
				break ;
			data->raydata.dst_towall += data->raydata.ray_step;
		}
		draw_ray(data, data->x);
		++data->x;
	}
	return (d);
}
