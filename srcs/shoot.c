/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/11/21 14:21:19 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		deal_damage_tomonster(t_wolf *data)
{
	data->monster->hp = data->monster->hp
		- data->player.wdata[data->player.weapon].damage;
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

	if (data->monster->data.dst_fromplayer
			> data->player.wdata[data->player.weapon].range)
		return (0);
	range = W_WIDTH / data->monster->data.dst_fromplayer / 2;
	i = W_WIDTH / 2 - range - 1;
	if (data->monster->data.mid < W_WIDTH / 2 + range
			&& data->monster->data.mid > W_WIDTH / 2 - range)
	{
		while (++i < W_WIDTH / 2 + range)
			if (data->map.depth_buffer[i] < data->monster->data.dst_fromplayer)
				return (0);
		return (1);
	}
	else
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
		{
			if (hitbox(data) == 1)
			{
				deal_damage_tomonster(data);
				break ;
			}
		}
		data->monster = data->monster->next;
	}
	data->monster = head;
}

void			shoot(t_wolf *data)
{
	if (data->event.type == SDL_KEYDOWN
			&& --data->shoot < 1 && data->fire_delay < 1)
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
		data->shoot = data->fire_delay;
	}
	else if (data->event.type == SDL_KEYUP)
		data->shoot = 0;
}
