/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/11/25 20:46:59 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static int		is_outrange(t_wolf *data)
{
	t_object	*head;

	if (data->player.y < 0 || data->player.y > data->map.height)
		return (1);
	else if (data->player.x < 0 || data->player.x > data->map.width)
		return (1);
	else if (data->map.map[(int)data->player.y * data->map.width
			+ (int)data->player.x] == 1)
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
	if (is_outrange(data))
	{
		data->player.x -= sx;
		data->player.y -= sy;
	}
	data->player.pos = (int)data->player.x
		+ data->map.width * (int)data->player.y;
}

static void		moves(t_wolf *data)
{
	if (data->key[KW])
		move_maker(data,
			cosf(data->player.angle) * data->player.speed * data->etime,
			sinf(data->player.angle) * data->player.speed * data->etime);
	if (data->key[KS])
		move_maker(data,
			-(cosf(data->player.angle) * data->player.speed * data->etime),
			-(sinf(data->player.angle) * data->player.speed * data->etime));
	if (data->key[KQ])
		move_maker(data,
			sinf(data->player.angle) * data->player.speed * data->etime,
			-(cosf(data->player.angle) * data->player.speed * data->etime));
	if (data->key[KD])
		move_maker(data,
			-(sinf(data->player.angle) * data->player.speed * data->etime),
			cosf(data->player.angle) * data->player.speed * data->etime);
}

static void		change_weapon(t_wolf *data)
{
	if (data->event.type == SDL_KEYDOWN)
	{
		if (data->player.weapon < 4)
			++data->player.weapon;
		if (data->player.weapon > 3)
			data->player.weapon = 0;
	}
}

static void		get_events(t_wolf *data)
{
	if (data->event.key.keysym.sym == SDLK_b || data->event.key.keysym.sym == SDLK_n)
		add_sc_x(data);
	else if (data->event.key.keysym.sym == SDLK_w)
		data->key[KW] = data->event.type == SDL_KEYDOWN ? 1 : 0;
	else if (data->event.key.keysym.sym == SDLK_a)
		data->key[KQ] = data->event.type == SDL_KEYDOWN ? 1 : 0;
	else if (data->event.key.keysym.sym == SDLK_s)
		data->key[KS] = data->event.type == SDL_KEYDOWN ? 1 : 0;
	else if (data->event.key.keysym.sym == SDLK_d)
		data->key[KD] = data->event.type == SDL_KEYDOWN ? 1 : 0;
	else if (data->event.key.keysym.sym == SDLK_m)
	{
		if (data->event.type == SDL_KEYDOWN)
			data->key[KM] = data->key[KM] ? 0 : 1;
	}
	else if (data->event.key.keysym.sym == SDLK_p)
	{
		if (data->event.type == SDL_KEYDOWN)
			data->key[KP] = data->key[KP] ? 0 : 1;
	}
}

void			events(t_wolf *data)
{
	SDL_PollEvent(&data->event);
	if (data->event.type == SDL_MOUSEMOTION)
	{
		SDL_GetRelativeMouseState(&(data->mouse.xrel), &(data->mouse.yrel));
		ft_mouse_motion_x(data);
	}
	else if (data->event.type == SDL_QUIT)
		clean_exit(data, NULL, 1);
	else if (data->event.key.keysym.sym == SDLK_ESCAPE)
		clean_exit(data, NULL, 1);
	if (data->key[KP])
		w_pause(data);
	if (data->event.key.keysym.sym == SDLK_SPACE)
		shoot(data);
	else if (data->event.key.keysym.sym == SDLK_z)
		change_weapon(data);
	else
		get_events(data);
	moves(data);
	SDL_FlushEvent(SDL_KEYUP | SDL_KEYDOWN | SDL_MOUSEMOTION);
}
