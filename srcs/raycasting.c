/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:05:22 by maboye            #+#    #+#             */
/*   Updated: 2019/11/22 14:45:10 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		draw_ray(t_wolf *data, int x)
{
	int			y;

	data->raydata.ceiling = (float)(W_HEIGHT / 2)
		- W_HEIGHT / data->raydata.dst_towall;
	data->raydata.floor = W_HEIGHT - data->raydata.ceiling;
	y = data->raydata.ceiling;
	while (++y < W_HEIGHT)
	{
		if (y <= data->raydata.floor)
		{
			data->raydata.sampley = ((float)y - (float)data->raydata.ceiling)
				/ ((float)data->raydata.floor - (float)data->raydata.ceiling);
			if (data->raydata.cdst < 0.1)
				put_pixel(data->screen, x, y, 0xFFFF00FF);
			else
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
	if (testx < 0 || testx >= data->map.width
			|| testy < 0 || testy >= data->map.height)
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

static void		get_cdst(t_wolf *data, int i)
{
	float	dst;
	float	vecx;
	float	vecy;

	if (data->map.map[i] == 1)
	{
		vecx = data->pfdata.list[i].x - data->player.x;
		vecy = data->pfdata.list[i].y - data->player.y;
		data->raydata.angle = atan2f(data->raydata.eyex, data->raydata.eyey)
			- atan2f(vecx, vecy);
		if (data->raydata.angle < -3.14159)
			data->raydata.angle += 2 * 3.14159;
		else if (data->raydata.angle > 3.14159)
			data->raydata.angle -= 2 * 3.14159;
		if (fabs(data->raydata.angle) < data->player.fov / 2)
		{
			dst = ft_sqrt(vecx * vecx + vecy * vecy);
			if (dst < data->raydata.cdst)
				data->raydata.cdst = dst;
		}
	}
}

static void		get_closerwall(t_wolf *data)
{
	int	i;

	data->raydata.cdst = data->map.depth;
	data->raydata.eyex = cosf(data->player.angle);
	data->raydata.eyey = sinf(data->player.angle);
	i = -1;
	while (++i < data->map.len)
		get_cdst(data, i);
	data->raydata.cdst -= 2;
	if (data->raydata.cdst < 0)
		data->raydata.cdst = 0;
	if (data->map.map[(int)data->player.x + 1
			+ data->map.width * (int)data->player.y] == 1
			|| data->map.map[(int)data->player.x - 1
			+ data->map.width * (int)data->player.y] == 1
			|| data->map.map[(int)data->player.x
			+ data->map.width * (int)data->player.y + 1] == 1
			|| data->map.map[(int)data->player.x
			+ data->map.width * (int)data->player.y - 1] == 1)
		data->raydata.cdst = 0;
}

void			raycasting(t_wolf *data)
{
	get_closerwall(data);
	data->i = -1;
	data->i_max = W_WIDTH;
	while (++data->i < data->i_max)
	{
		data->raydata.angle = (data->player.angle - data->player.fov / 2)
			+ ((float)data->i / (float)W_WIDTH) * data->player.fov;
		data->raydata.eyex = cosf(data->raydata.angle);
		data->raydata.eyey = sinf(data->raydata.angle);
		data->raydata.dst_towall = data->raydata.cdst;
		while (hitwall(data) == 0)
			data->raydata.dst_towall += data->raydata.ray_step;
		draw_ray(data, data->i);
		data->map.depth_buffer[data->i] = data->raydata.dst_towall;
	}
}
