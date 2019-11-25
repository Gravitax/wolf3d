/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebosson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:30:19 by bebosson          #+#    #+#             */
/*   Updated: 2019/11/25 20:10:17 by bebosson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	set_write_to_screen(t_wolf *data, SDL_Rect rect, int color, char *str, TTF_Font *pl)
{
	SDL_Surface *surface;
	SDL_Texture *texture;

	SDL_SetRenderDrawColor(data->renderer, (color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff, 0);
	surface = TTF_RenderText_Solid(pl, str, ft_hex_to_rgb(color));
	texture = SDL_CreateTextureFromSurface(data->renderer, surface);
	SDL_QueryTexture(texture, 0, 0, &(rect.w), &(rect.h));
	SDL_RenderCopy(data->renderer, texture, NULL, &rect);
}

void set_rect_to_screen(t_wolf *data, SDL_Rect *rect, int color)
{
	SDL_SetRenderDrawColor(data->renderer, (color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff, 100);
	SDL_RenderFillRect(data->renderer, rect);
}

void		add_sc_x(t_wolf *data)
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
