/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:05:22 by maboye            #+#    #+#             */
/*   Updated: 2019/11/29 16:22:13 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static int		in_wall(t_wolf *data)
{
	int	i;

	i = -1;
	while (++i < data->map.len)
		if (data->pfdata.list[i].bobstacle == 1)
		{
			if (distance(data->player.x,
					data->player.y,
					data->pfdata.list[i].x + 0.5f,
					data->pfdata.list[i].y + 0.5f) < 0.8f)
				return (1);
		}
	return (0);
}

static int		is_outrange(t_wolf *data)
{
	t_object	*head;

	if (data->player.y < 0 || data->player.y > data->map.height)
		return (1);
	else if (data->player.x < 0 || data->player.x > data->map.width)
		return (1);
	if (in_wall(data) == 1)
		return (1);
	head = data->monster;
	while (data->monster)
	{
		if (distance(data->player.x, data->player.y,
		data->monster->x, data->monster->y) < 1)
		{
			data->monster = head;
			return (1);
		}
		data->monster = data->monster->next;
	}
	data->monster = head;
	return (0);
}

static void		move_maker(t_wolf *data, float sx, float sy)
{
	data->player.x += sx;
	data->player.y += sy;
	if (is_outrange(data) == 1)
	{
		data->player.x -= sx;
		data->player.y -= sy;
		SDL_FlushEvent(SDL_KEYDOWN);
	}
	data->player.pos = (int)data->player.x
		+ data->map.width * (int)data->player.y;
}

void			movements(t_wolf *data)
{
	float	shift;

	shift = data->key[SHIFT] ? 1.5f : 1;
	if (data->key[KQ])
		data->player.angle -= data->player.speed * data->player.ms * 10;
	if (data->key[KE])
		data->player.angle += data->player.speed * data->player.ms * 10;
	if (data->key[KW])
		move_maker(data,
			cosf(data->player.angle) * data->player.speed * shift,
			sinf(data->player.angle) * data->player.speed * shift);
	if (data->key[KS])
		move_maker(data,
			-(cosf(data->player.angle) * data->player.speed * shift),
			-(sinf(data->player.angle) * data->player.speed * shift));
	if (data->key[KA])
		move_maker(data,
			sinf(data->player.angle) * data->player.speed * shift,
			-(cosf(data->player.angle) * data->player.speed * shift));
	if (data->key[KD])
		move_maker(data,
			-(sinf(data->player.angle) * data->player.speed * shift),
			cosf(data->player.angle) * data->player.speed * shift);
}
