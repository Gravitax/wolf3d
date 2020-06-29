/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:47:19 by maboye            #+#    #+#             */
/*   Updated: 2019/12/04 20:30:37 by bebosson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		draw_player_minimap(t_wolf *d, int x, int y)
{
	d->raydata.eyex = cosf(d->raydata.angle - 5 * 3.14159 / 6);
	d->raydata.eyey = sinf(d->raydata.angle - 5 * 3.14159 / 6);
	d->point[0].x = 10 * (d->raydata.eyex) + x;
	d->point[0].y = 10 * (d->raydata.eyey) + y;
	d->point[1].x = 10 * cosf(d->raydata.angle + 5 * 3.14159 / 6) + x;
	d->point[1].y = 10 * sinf(d->raydata.angle + 5 * 3.14159 / 6) + y;
	SDL_SetRenderDrawColor(d->renderer, 0, 255, 0, 100);
	SDL_RenderDrawLine(d->renderer, x, y, d->point[0].x, d->point[0].y);
	SDL_RenderDrawLine(d->renderer, x, y, d->point[1].x, d->point[1].y);
	SDL_RenderDrawLine(d->renderer,
			d->point[0].x, d->point[0].y,
			d->point[1].x, d->point[1].y);
}

static void		draw_ray_fov(t_wolf *data, int i, int x, int y)
{
	data->raydata.angle = (data->player.angle - data->player.fov / 2)
		+ ((float)i / (float)W_WIDTH) * data->player.fov;
	SDL_SetRenderDrawColor(data->renderer, 155, 0, 150, 100);
	if (i == W_WIDTH / 2)
		draw_player_minimap(data, x, y);
	SDL_RenderDrawLine(data->renderer, x, y,
			data->map.depth_buffer[i]
			* W_WIDTH / (data->map.sc_x * data->map.width)
			* (cosf(data->raydata.angle)) + x, data->map.depth_buffer[i]
			* W_HEIGHT / (data->map.sc_x * data->map.height)
			* (sinf(data->raydata.angle)) + y);
}

static void		calc_player(t_wolf *d)
{
	int			i;

	d->pl->x = d->player.x * W_WIDTH / (d->map.sc_x * d->map.width);
	d->pl->y = d->player.y * W_HEIGHT / (d->map.sc_x * d->map.height);
	SDL_SetRenderDrawColor(d->renderer, 0, 0xFF, 0, 0);
	i = -1;
	while (++i < W_WIDTH)
		draw_ray_fov(d, i, d->pl->x, d->pl->y);
	SDL_SetRenderDrawColor(d->renderer, 155, 150, 150, 100);
	draw_ray_fov(d, i / 2, d->pl->x, d->pl->y);
}

static void		draw_minimap(t_wolf *data, int nx)
{
	int			ny;

	ny = -1;
	data->rect->h = 2 * W_HEIGHT / (data->map.sc_x * data->map.height);
	data->rect->w = 2 * W_WIDTH / (data->map.sc_x * data->map.width);
	while (++ny < data->map.height)
	{
		data->rect->x = nx * W_WIDTH / (data->map.sc_x * data->map.width);
		data->rect->y = ny * W_HEIGHT / (data->map.sc_x * data->map.height);
		if (data->map.map[ny * data->map.width + nx] == 1)
			SDL_SetRenderDrawColor(data->renderer, 255, 0, 0, 100);
		else
			SDL_SetRenderDrawColor(data->renderer, 155, 0, 0, 100);
		SDL_RenderFillRect(data->renderer, data->rect);
	}
}

void			minimap(t_wolf *data)
{
	int			nx;
	int			ny;

	nx = -1;
	while (++nx < data->map.width)
		draw_minimap(data, nx);
	nx = -1;
	while (++nx < data->map.width)
	{
		ny = -1;
		while (++ny < data->map.height)
		{
			if ((ny + 1) * data->map.width + nx == data->player.pos)
				calc_player(data);
		}
	}
	object_minimap(data, data->monster);
}
