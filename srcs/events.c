/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/11/19 18:39:45 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static int		is_outrange(t_wolf *data)
{
	if (data->player.y < 0 || data->player.y > data->map.height)
		return (1);
	else if (data->player.x < 0 || data->player.x > data->map.width)
		return (1);
	else if (data->map.map[(int)data->player.y * data->map.width
	+ (int)data->player.x] == 1)
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
	/*if (data->key[KA])
		data->player.angle -= data->player.speed
			* data->etime * data->player.ms;
    if (data->key[KE])
		data->player.angle += data->player.speed
			* data->etime * data->player.ms;
	
	if (data->key[KA])
	{
		data->player.angle = data->event.motion
	}*/
	if (data->key[KZ])
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

static void		add_sc_x(t_wolf *data)
{
	if (data->event.key.keysym.sym == SDLK_b)
	{
			data->key[KB] = data->event.type == SDL_KEYDOWN ? 1 : 0;
			if (data->key[KB] == 1 && data->map.sc_x < 5)
				data->map.sc_x++;
	}
	else if (data->event.key.keysym.sym == SDLK_n)
	{
			data->key[KN] = data->event.type == SDL_KEYDOWN ? 1 : 0;
			if (data->key[KN] == 1 && data->map.sc_x > 2)
				data->map.sc_x--;
	}
}

static void		change_weapon(t_wolf *data)
{
		data->key[KZ] = data->event.type == SDL_KEYDOWN ? 1 : 0;
		if (data->player.weapon < 4 && data->key[KZ] == 1)
			data->player.weapon++;
		if (data->player.weapon == 4 && data->key[KZ] == 1)
			data->player.weapon = 0;
		data->key[KZ] = 0;
}

void static		ft_mouse_motion_x(t_wolf *data)
{
	if (data->mouse.x > 0.0)
		data->player.angle = (int)(data->player.angle + abs(data->mouse.x) / 20) % 360;
	else if (data->mouse.x < 0.0)
	{
		data->player.angle = (int)(data->player.angle - abs(data->mouse.x) / 20) % 360;
		if (data->player.angle < 0)
			data->player.angle = 360 + data->player.angle;
	}
}

void static		get_events(t_wolf *data)
{
	if (data->event.key.keysym.sym == SDLK_q)
		data->key[KA] = data->event.type == SDL_KEYDOWN? 1 : 0;
	else if (data->event.key.keysym.sym == SDLK_e)
		data->key[KE] = data->event.type == SDL_KEYDOWN ? 1 : 0;
	else if (data->event.key.keysym.sym == SDLK_w)
		data->key[KZ] = data->event.type == SDL_KEYDOWN ? 1 : 0;
	else if (data->event.key.keysym.sym == SDLK_q)
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
	else if (data->event.key.keysym.sym == SDLK_b || data->event.key.keysym.sym == SDLK_n)
		add_sc_x(data); // proportion de la map => b pour diminuer n pour augmenter 
	else if (data->event.key.keysym.sym == SDLK_z) 
		change_weapon(data);
			
}

void            events(t_wolf *data)
{
    SDL_PollEvent(&data->event);
    if (data->event.type == SDL_MOUSEMOTION)
	{
		SDL_GetRelativeMouseState(&(data->mouse.x), &(data->mouse.y));	
		ft_mouse_motion_x(data);
	}
	if (data->event.type == SDL_QUIT)
        clean_exit(data, NULL, 1);
    else if (data->event.key.keysym.sym == SDLK_ESCAPE)
        clean_exit(data, NULL, 1);
	else if (data->event.key.keysym.sym == SDLK_SPACE)
		shoot(data);
	else
    	get_events(data);
	moves(data);
	SDL_FlushEvent(SDL_KEYUP | SDL_KEYDOWN | SDL_MOUSEMOTION);
}
