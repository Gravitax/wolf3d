/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:05:22 by maboye            #+#    #+#             */
/*   Updated: 2019/11/29 12:34:34 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		draw_ray(t_wolf *data, int x)
{
	int			y;
	float		size;

	data->raydata.ceiling = (float)(W_HEIGHT / 2)
		- W_HEIGHT / data->raydata.dst_towall;
	data->raydata.floor = W_HEIGHT - data->raydata.ceiling;
	size = ((float)data->raydata.floor - (float)data->raydata.ceiling);
	y = data->raydata.ceiling;
	while (++y < W_HEIGHT)
	{
		if (y <= data->raydata.floor)
		{
			data->raydata.sampley = ((float)y - (float)data->raydata.ceiling)
				/ size;
			put_pixel(data->screen, x, y, get_pixel(data, data->raydata.si,
				data->raydata.samplex, data->raydata.sampley));
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
	if (testx < 0 || testx > data->map.width
		|| testy < 0 || testy > data->map.height)
	{
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

static void		get_closerwall(t_wolf *data)
{
	int		i;
	float	dst;

	data->cdst = data->map.depth;
	i = -1;
	while (++i < data->map.len)
		if (data->pfdata.list[i].bobstacle == 1)
		{
			dst = distance(data->player.x, data->player.y,
				data->pfdata.list[i].x, data->pfdata.list[i].y);
			if (dst < data->cdst)
				data->cdst = dst;
		}
	data->cdst -= 1.5f;
	if (data->cdst < 0)
		data->cdst = 0;
}

void			raycasting(t_wolf *data)
{
	int		x;
	float	nfisheye;

	get_closerwall(data);
	x = -1;
	while (++x < W_WIDTH)
	{
		data->raydata.angle = ((float)x / (float)W_WIDTH) * data->player.fov
			+ (data->player.angle - data->player.fov / 2);
		data->raydata.eyex = cosf(data->raydata.angle);
		data->raydata.eyey = sinf(data->raydata.angle);
		nfisheye = ((float)x / (float)W_WIDTH * data->player.fov)
			- data->player.fov / 2;
		data->raydata.dst_towall = data->cdst;
		while (hitwall(data) == 0)
			data->raydata.dst_towall += data->raydata.ray_step;
		data->raydata.dst_towall *= cos(nfisheye);
		draw_ray(data, x);
		data->map.depth_buffer[x] = data->raydata.dst_towall;
	}
}
