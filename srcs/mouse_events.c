/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:05:22 by maboye            #+#    #+#             */
/*   Updated: 2019/11/26 17:57:24 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			change_weapon(t_wolf *data)
{
	static int	delay = 0;

	if (--delay < 0)
	{
		if (data->player.weapon < 4)
			++data->player.weapon;
		if (data->player.weapon > 3)
			data->player.weapon = 0;
		delay = 20;
	}
}

void			ft_mouse_motion_x(t_wolf *data)
{
	int			x;
	int			y;
	static int	token = 0;

	if (token == 1)
	{
		data->player.angle -= data->player.speed
			* data->etime * data->player.ms * data->mouse.xrel;
		token = 0;
	}
	else if (token == 0)
	{
		SDL_GetWindowPosition(data->pwindow, &x, &y);
		SDL_WarpMouseInWindow(data->pwindow,
			x - W_WIDTH / 2,
			y - W_HEIGHT / 2);
		token = 1;
		SDL_ShowCursor(SDL_DISABLE);
	}
	SDL_FlushEvent(SDL_KEYUP | SDL_KEYDOWN | SDL_MOUSEMOTION);
}
