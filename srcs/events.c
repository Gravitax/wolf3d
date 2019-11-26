/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/11/26 17:05:28 by maboye           ###   ########.fr       */
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
	if (data->key[KQ])
		data->player.angle -= data->player.speed
			* data->etime * data->player.ms;
	if (data->key[KE])
		data->player.angle += data->player.speed
			* data->etime * data->player.ms;
	if (data->key[KW])
		move_maker(data,
			cosf(data->player.angle) * data->player.speed * data->etime,
			sinf(data->player.angle) * data->player.speed * data->etime);
	if (data->key[KS])
		move_maker(data,
			-(cosf(data->player.angle) * data->player.speed * data->etime),
			-(sinf(data->player.angle) * data->player.speed * data->etime));
	if (data->key[KA])
		move_maker(data,
			sinf(data->player.angle) * data->player.speed * data->etime,
			-(cosf(data->player.angle) * data->player.speed * data->etime));
	if (data->key[KD])
		move_maker(data,
			-(sinf(data->player.angle) * data->player.speed * data->etime),
			cosf(data->player.angle) * data->player.speed * data->etime);
}

static void		get_events(t_wolf *data)
{
	if (data->event.key.keysym.sym == SDLK_b
	|| data->event.key.keysym.sym == SDLK_n)
		add_sc_x(data);
	else if (data->event.key.keysym.sym == SDLK_q)
		data->key[KQ] = data->event.type == SDL_KEYDOWN ? 1 : 0;
	else if (data->event.key.keysym.sym == SDLK_e)
		data->key[KE] = data->event.type == SDL_KEYDOWN ? 1 : 0;
	else if (data->event.key.keysym.sym == SDLK_w)
		data->key[KW] = data->event.type == SDL_KEYDOWN ? 1 : 0;
	else if (data->event.key.keysym.sym == SDLK_a)
		data->key[KA] = data->event.type == SDL_KEYDOWN ? 1 : 0;
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
	if (data->event.type == SDL_QUIT
	|| data->event.key.keysym.sym == SDLK_ESCAPE)
		clean_exit(data, NULL, 1);
	else if (data->key[KP])
		w_pause(data);
	else if (data->event.button.button == SDL_BUTTON_RIGHT)
		change_weapon(data);
	else if (data->event.button.button == SDL_BUTTON_LEFT)
		shoot(data);
	else
		get_events(data);
	moves(data);
	SDL_FlushEvent(SDL_KEYUP | SDL_KEYDOWN | SDL_MOUSEMOTION);
}
