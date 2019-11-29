/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:05:22 by maboye            #+#    #+#             */
/*   Updated: 2019/11/29 18:59:49 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		change_weapon(t_wolf *data)
{
	static int	delay = 0;

	if (--delay < 0)
	{
		if (data->player.weapon < 4)
		{
			++data->player.weapon;
			play_sound(data, data->sound.switchgun, 7);
		}
		if (data->player.weapon > 3)
		{
			data->player.weapon = 0;
			play_sound(data, data->sound.hand, 7);
		}
		delay = 10;
		SDL_FlushEvent(SDL_MOUSEBUTTONDOWN);
	}
}

static void		mouse_motion(t_wolf *data)
{
	data->player.angle += data->player.speed
		* data->player.ms * data->mouse.xrel;
	if (ft_abs(data->mouse.xrel) > W_WIDTH / 2
	|| data->mouse.x > data->wx + W_WIDTH
	|| data->mouse.x < data->wx
	|| data->mouse.y > data->wy + W_HEIGHT
	|| data->mouse.y < data->wy)
		SDL_WarpMouseGlobal(data->wx + W_WIDTH / 2,
			data->wy + W_HEIGHT / 2);
}

void			mouse_events(t_wolf *data)
{
	SDL_ShowCursor(SDL_DISABLE);
	SDL_GetGlobalMouseState(&(data->mouse.x), &(data->mouse.y));
	SDL_GetRelativeMouseState(&(data->mouse.xrel), &(data->mouse.yrel));
	if (data->key[ML])
		shoot(data);
	if (data->key[MR])
		change_weapon(data);
	mouse_motion(data);
	SDL_FlushEvent(SDL_MOUSEMOTION);
}
