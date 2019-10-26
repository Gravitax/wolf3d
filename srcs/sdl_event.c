/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sdl_event.c                                 :+:      :+:    :+:   */
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

static void		movemaker(t_wolf *data, float sx, float sy)
{
	data->player.x += sx;
	data->player.y += sy;

	if (is_outrange(data))
	{
		data->player.x -= sx;
		data->player.y -= sy;
	}
}

static void		movehandler(t_wolf *data)
{
    if (data->key[KA])
		data->player.angle += data->player.speed;
	if (data->key[KE])
		data->player.angle -= data->player.speed;
	if (data->key[KZ])
		movemaker(data,
            -(cosf(data->player.angle) * data->player.speed),
            -(sinf(data->player.angle) * data->player.speed));
	if (data->key[KS])
		movemaker(data,
            cosf(data->player.angle) * data->player.speed,
            sinf(data->player.angle) * data->player.speed);
	if (data->key[KQ])
		movemaker(data,
            -(sinf(data->player.angle) * data->player.speed),
            cosf(data->player.angle) * data->player.speed);
	if (data->key[KD])
		movemaker(data,
            sinf(data->player.angle) * data->player.speed,
            -(cosf(data->player.angle) * data->player.speed));
}

void            key_event(t_wolf *data)
{
	if (data->event.key.keysym.sym == SDLK_a)
		data->key[KA] = data->event.type == SDL_KEYUP ? 1 : 0;
	if (data->event.key.keysym.sym == SDLK_e)
		data->key[KE] = data->event.type == SDL_KEYUP ? 1 : 0;
	if (data->event.key.keysym.sym == SDLK_z)
		data->key[KZ] = data->event.type == SDL_KEYUP ? 1 : 0;
	if (data->event.key.keysym.sym == SDLK_s)
		data->key[KS] = data->event.type == SDL_KEYUP ? 1 : 0;
	if (data->event.key.keysym.sym == SDLK_d)
		data->key[KD] = data->event.type == SDL_KEYUP ? 1 : 0;
	if (data->event.key.keysym.sym == SDLK_q)
		data->key[KQ] = data->event.type == SDL_KEYUP ? 1 : 0;
	movehandler(data);
}

void            sdl_event(t_wolf *data)
{
    SDL_PollEvent(&data->event);
    if (data->event.type == SDL_QUIT)
        clean_exit(data, NULL, 1);
    if (data->event.key.keysym.sym == SDLK_ESCAPE)
        clean_exit(data, NULL, 1);
    key_event(data);
}
