/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:05:22 by maboye            #+#    #+#             */
/*   Updated: 2019/11/28 14:41:01 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		change_weapon(t_wolf *data)
{
	static int	delay = 0;

	if (--delay < 0)
	{
		if (data->player.weapon < 4)
			++data->player.weapon;
		if (data->player.weapon > 3)
			data->player.weapon = 0;
		delay = 10;
		SDL_FlushEvent(SDL_MOUSEBUTTONDOWN);
	}
}

static void		mouse_motion(t_wolf *data)
{
	static int	token = 0;

	if (token == 1)
	{
		data->player.angle += data->player.speed
			* data->player.ms * data->mouse.xrel;
		token = 0;
	}
	if (token == 0)
	{
		if (ft_abs(data->mouse.xrel) > W_WIDTH / 2
		|| data->mouse.x > 600 + W_WIDTH
		|| data->mouse.x < 600
		|| data->mouse.y > 600 + W_HEIGHT
		|| data->mouse.y < 600)
			SDL_WarpMouseGlobal(600 + W_WIDTH / 2, 600 + W_HEIGHT / 2);
		token = 1;
	}
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
