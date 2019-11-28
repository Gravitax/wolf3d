/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/11/28 12:34:40 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		deal_damage_tomonster(t_wolf *data)
{
	data->monster->hp -= data->player.wdata[data->player.weapon].damage;
	if (data->monster->hp < 1)
	{
		++data->kill_score;
		data->monster->dead = 1;
		data->monster->si = 28;
	}
	else
		data->monster->si = data->monster->type + 6;
}

static int		hitbox(t_wolf *data)
{
	int	i;
	int	range;
	int	ms;

	ms = W_WIDTH / 2;
	if (data->monster->data.dst_fromplayer
			> data->player.wdata[data->player.weapon].range)
		return (0);
	range = ms / data->monster->data.dst_fromplayer;
	i = ms - range - 1;
	if (data->monster->data.mid < ms + range
		&& data->monster->data.mid > ms - range)
	{
		while (++i < ms + range)
			if (data->map.depth_buffer[i] >= data->monster->data.dst_fromplayer)
				return (1);
	}
	return (0);
}

static void		shoot_impact(t_wolf *data)
{
	t_object	*head;

	head = data->monster;
	while (data->monster)
	{
		if (data->monster->type > 6
			&& fabs(data->monster->data.angle) < data->player.fov / 2
			&& data->monster->data.dst_fromplayer < data->map.depth)
			if (hitbox(data) == 1)
				deal_damage_tomonster(data);
		data->monster = data->monster->next;
	}
	data->monster = head;
}

void			shoot(t_wolf *data)
{
	if (data->key[ML] && data->fire_delay < 1)
	{
		if (data->player.weapon == 0)
			data->player.wdata[data->player.weapon].si = 21;
		else if (data->player.weapon == 1)
			data->player.wdata[data->player.weapon].si = 23;
		else if (data->player.weapon == 2)
			data->player.wdata[data->player.weapon].si = 25;
		else if (data->player.weapon == 3)
			data->player.wdata[data->player.weapon].si = 27;
		shoot_impact(data);
		data->fire_delay = data->player.wdata[data->player.weapon].delay;
		data->skin_delay = 10;
	}
}
