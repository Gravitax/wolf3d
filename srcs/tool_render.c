/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebosson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:30:19 by bebosson          #+#    #+#             */
/*   Updated: 2019/11/25 22:18:46 by bebosson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	set_write_to_screen(t_wolf *data, SDL_Rect rect, int c, char *str)
{
	SDL_Surface *surface;
	SDL_Texture *texture;

	surface = TTF_RenderText_Solid(data->policep, str, ft_hex_to_rgb(c));
	texture = SDL_CreateTextureFromSurface(data->renderer, surface);
	SDL_QueryTexture(texture, 0, 0, &(rect.w), &(rect.h));
	SDL_RenderCopy(data->renderer, texture, NULL, &rect);
}

void	set_rect_to_screen(t_wolf *data, SDL_Rect *rect, int c)
{
	int a;

	a = 0xff;
	SDL_SetRenderDrawColor(data->renderer, c >> 16 & a, c >> 8 & a, c & a, 1);
	SDL_RenderFillRect(data->renderer, rect);
}

void	add_sc_x(t_wolf *data)
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
