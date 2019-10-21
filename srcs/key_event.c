/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyup_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:30:54 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void            key_event(t_wolf *data)
{
	if (data->event.key.keysym.sym == SDLK_a)
		data->player.angle -= 0.1;
	if (data->event.key.keysym.sym == SDLK_e)
		data->player.angle += 0.1;


	if (data->event.key.keysym.sym == SDLK_z)
	{
		data->player.x += cosf(data->player.angle)
			* data->player.speed;
		data->player.y += sinf(data->player.angle)
			* data->player.speed;

		if (data->map.map[(int)data->player.y * data->map.width
			+ (int)data->player.x] == 1)
		{
			data->player.x -= cosf(data->player.angle)
				* data->player.speed;
			data->player.y -= sinf(data->player.angle)
				* data->player.speed;
		}
	}
	if (data->event.key.keysym.sym == SDLK_s)
	{
		data->player.x -= sinf(data->player.angle)
			* data->player.speed;
		data->player.y -= cosf(data->player.angle)
			* data->player.speed;

		if (data->map.map[(int)data->player.y * data->map.width
			+ (int)data->player.x] == 1)
		{
			data->player.x += sinf(data->player.angle)
				* data->player.speed;
			data->player.y += cosf(data->player.angle)
				* data->player.speed;
		}
	}
	if (data->event.key.keysym.sym == SDLK_d)
	{
		data->player.x -= sinf(data->player.angle)
			* data->player.speed;
		data->player.y += cosf(data->player.angle)
			* data->player.speed;

		if (data->map.map[(int)data->player.y * data->map.width
			+ (int)data->player.x] == 1)
		{
			data->player.x += sinf(data->player.angle)
				* data->player.speed;
			data->player.y -= cosf(data->player.angle)
				* data->player.speed;
		}
	}
	if (data->event.key.keysym.sym == SDLK_q)
	{
		data->player.x += sinf(data->player.angle)
			* data->player.speed;
		data->player.y -= cosf(data->player.angle)
			* data->player.speed;

		if (data->map.map[(int)data->player.y * data->map.width
			+ (int)data->player.x] == 1)
		{
			data->player.x -= sinf(data->player.angle)
				* data->player.speed;
			data->player.y += cosf(data->player.angle)
				* data->player.speed;
		}
	}
}
