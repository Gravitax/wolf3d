/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:05:22 by maboye            #+#    #+#             */
/*   Updated: 2019/11/27 19:38:47 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			change_weapon(t_wolf *data)
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
	}
}

static void		mouse_motion(t_wolf *data)
{
	static int	token = 0;

	SDL_GetRelativeMouseState(&(data->mouse.xrel), &(data->mouse.yrel));
	if (token == 1)
	{
		data->player.angle -= data->player.speed
			* data->etime * data->player.ms * data->mouse.xrel;
		token = 0;
	}
	else if (token == 0)
	{
		SDL_WarpMouseInWindow(data->pwindow,
			W_WIDTH / 2, W_HEIGHT / 2);
		token = 1;
	}
	SDL_FlushEvent(SDL_MOUSEMOTION);
}

void			mouse_events(t_wolf *data)
{
	SDL_ShowCursor(SDL_DISABLE);
	mouse_motion(data);
}
