/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:05:22 by maboye            #+#    #+#             */
/*   Updated: 2019/12/14 01:21:01 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		change_weapon(t_wolf *data)
{
	if (data->player.weapon < 4)
		++data->player.weapon;
	if (data->player.weapon > 3)
		data->player.weapon = 0;
	SDL_FlushEvent(SDL_MOUSEBUTTONDOWN);
}

void			mouse(t_wolf *data, Sint16 xrel, int dir)
{
	double	olddirx;
	double	oldplanex;
	double	angle;
	
	angle = xrel * M_PI / 180 * dir;
	olddirx = data->player.dirx;	
	data->player.dirx = (data->player.dirx * cos(angle)) - (data->player.diry * sin(angle));
	data->player.diry = (olddirx * sin(angle)) + (data->player.diry * cos(angle));
	oldplanex = data->player.planex;
	data->player.planex = (oldplanex * cos(angle)) - (data->player.planey * sin(angle));
	data->player.planey = (oldplanex * sin(angle)) + (data->player.planey * cos(angle));
}

static void		mouse_motion(t_wolf *data)
{
	
	double	olddirx;
	double	oldplanex;
	double	angle;
	
	mouse(data, data->mouse.xrel, 1);
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
