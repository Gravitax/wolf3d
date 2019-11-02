/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:30:54 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static int		is_outrange(t_wolf *data)
{
	if (data->map.map[(int)data->player.y * data->map.width
	+ (int)data->player.x] == 1)
		return (1);
	else if (data->player.y < 0 || data->player.y > data->map.height)
		return (1);
	else if (data->player.x < 0 || data->player.x > data->map.width)
		return (1);
	else
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
}

static void		moves(t_wolf *data)
{
    if (data->key[KA])
		data->player.angle += data->player.speed
			* data->etime * data->player.ms;
	if (data->key[KE])
		data->player.angle -= data->player.speed
			* data->etime * data->player.ms;
	if (data->key[KZ])
		move_maker(data,
            -(cosf(data->player.angle) * data->player.speed * data->etime),
            -(sinf(data->player.angle) * data->player.speed * data->etime));
	if (data->key[KQ])
		move_maker(data,
            -(sinf(data->player.angle) * data->player.speed * data->etime),
            cosf(data->player.angle) * data->player.speed * data->etime);
	if (data->key[KS])
		move_maker(data,
            cosf(data->player.angle) * data->player.speed * data->etime,
            sinf(data->player.angle) * data->player.speed * data->etime);
	if (data->key[KD])
		move_maker(data,
            sinf(data->player.angle) * data->player.speed * data->etime,
            -(cosf(data->player.angle) * data->player.speed * data->etime));
}

static void		get_events(t_wolf *data)
{
	if (data->event.key.keysym.sym == SDLK_a)
		data->key[KA] = data->event.type == SDL_KEYUP ? 1 : 0;
	else if (data->event.key.keysym.sym == SDLK_e)
		data->key[KE] = data->event.type == SDL_KEYUP ? 1 : 0;
	else if (data->event.key.keysym.sym == SDLK_z)
		data->key[KZ] = data->event.type == SDL_KEYUP ? 1 : 0;
	else if (data->event.key.keysym.sym == SDLK_q)
		data->key[KQ] = data->event.type == SDL_KEYUP ? 1 : 0;
	else if (data->event.key.keysym.sym == SDLK_s)
		data->key[KS] = data->event.type == SDL_KEYUP ? 1 : 0;
	else if (data->event.key.keysym.sym == SDLK_d)
		data->key[KD] = data->event.type == SDL_KEYUP ? 1 : 0;
	else if (data->event.key.keysym.sym == SDLK_m)
	{
		if (data->event.type == SDL_KEYDOWN)
			data->key[KM] = data->key[KM] ? 0 : 1;
	}
}

void            events(t_wolf *data)
{
    SDL_PollEvent(&data->event);
    if (data->event.type == SDL_QUIT)
        clean_exit(data, NULL, 1);
    if (data->event.key.keysym.sym == SDLK_ESCAPE)
        clean_exit(data, NULL, 1);
    get_events(data);
	moves(data);
	SDL_FlushEvent(SDL_KEYUP | SDL_KEYDOWN | SDL_MOUSEMOTION);
}
