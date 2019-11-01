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

static void		draw_ray(t_wolf *data, int x)
{
	int			y;

	data->raydata.ceiling = (float)(W_HEIGHT / 2)
		- W_HEIGHT / data->raydata.dst_towall;
	data->raydata.floor = W_HEIGHT - data->raydata.ceiling;
	y = data->raydata.ceiling;
    while (++y < W_HEIGHT)
	{
		if (y <= data->raydata.floor && data->raydata.dst_towall < data->map.depth)
		{
			data->raydata.sampley = ((float)y - (float)data->raydata.ceiling)
				/ ((float)data->raydata.floor - (float)data->raydata.ceiling);
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
	data->i = 0;
	data->i_max = W_WIDTH;
	while (data->i < data->i_max)
	{
		data->raydata.angle = (data->player.angle - data->player.fov / 2)
			+ ((float)data->i / (float)W_WIDTH) * data->player.fov;
		data->raydata.dst_towall = 0;
		data->raydata.eyex = cosf(data->raydata.angle);
		data->raydata.eyey = sinf(data->raydata.angle);
		while (data->raydata.dst_towall < data->map.depth)
		{
			if (hitwall(data) == 1)
				break ;
			data->raydata.dst_towall += data->raydata.ray_step;
		}
		draw_ray(data, data->i);
		++data->i;
	}
	return (d);
}
