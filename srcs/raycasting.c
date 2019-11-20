/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:05:22 by maboye            #+#    #+#             */
/*   Updated: 2019/11/05 14:09:52 by maboye           ###   ########.fr       */
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

static void     get_closerwall(t_wolf *data)
{
    float   vecx;
    float   vecy;
	float	dst;

    data->raydata.cdst = data->map.depth;
    data->raydata.eyex = cosf(data->player.angle);
    data->raydata.eyey = sinf(data->player.angle);
    for (int i = 0; i < data->map.len; i++)
    {
        if (data->pfdata.list[i].wall == 1)
        {
            vecx = data->pfdata.list[i].x - data->player.x;
            vecy = data->pfdata.list[i].y - data->player.y;
            data->raydata.angle = atan2f(data->raydata.eyex,
				data->raydata.eyey) - atan2f(vecx, vecy);
            if (fabs(data->raydata.angle) < data->player.fov / 2)
            {
				dst = ft_sqrt(vecx * vecx + vecy * vecy);
                //dst = Q_sqrt(vecx * vecx + vecy * vecy);
                if (dst < data->raydata.cdst)
                    data->raydata.cdst = dst;
            }
        }
    }
	if (data->pfdata.list[(int)data->player.x + 1
		+ data->map.width * (int)data->player.y].wall == 1
	|| data->pfdata.list[(int)data->player.x - 1
		+ data->map.width * (int)data->player.y].wall == 1
	|| data->pfdata.list[(int)data->player.x
		+ data->map.width * (int)data->player.y + 1].wall == 1
	|| data->pfdata.list[(int)data->player.x
		+ data->map.width * (int)data->player.y - 1].wall == 1)
		data->raydata.cdst = 0;

    data->raydata.cdst -= 2;
    if (data->raydata.cdst < 0)
        data->raydata.cdst = 0;
}

void			*raycasting(void *d)
{
	t_wolf	*data;

	data = (t_wolf *)d;
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
		if (data->raydata.dst_towall < 0.1)
			continue ;
		draw_ray(data, data->i);
		data->map.depth_buffer[data->i] = data->raydata.dst_towall;
	}
	return (d);
}
