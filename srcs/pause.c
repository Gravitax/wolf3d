/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:33:16 by bebosson          #+#    #+#             */
/*   Updated: 2019/12/02 18:52:42 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

SDL_Color			ft_hex_to_rgb(int hexa)
{
	SDL_Color color;

	color.r = hexa >> 24;
	color.g = hexa >> 16;
	color.b = hexa >> 8;
	color.a = hexa;
	return (color);
}

static int			move_cursor(t_wolf *data, int *cursor)
{
	if (data->event.key.keysym.sym == SDLK_UP && *cursor > 1)
		return (--*cursor);
	else if (data->event.key.keysym.sym == SDLK_DOWN && *cursor < 2)
		return (++*cursor);
	else
		return (*cursor);
}

static void			draw_cursor(t_wolf *data, int cursor, SDL_Rect rect)
{
	SDL_Rect	rect_cursor;
	int			x;

	x = 7;
	while (x < 11)
	{
		rect_cursor = (SDL_Rect){x * UNITX, (6.5 + cursor)
			* UNITY, UNITX / 6, UNITY / 6};
		set_rect_to_screen(data, &rect_cursor, 0);
		x++;
	}
	rect_cursor = (SDL_Rect){x * UNITX, (6 + cursor)
		* UNITY, UNITX / 2, UNITY / 2};
	set_rect_to_screen(data, &rect_cursor, 0);
}

static void			draw_main_rect(t_wolf *data, int cursor)
{
	SDL_Rect	rect;
	SDL_Rect	rect2;
	SDL_Rect	rect_cursor;
	int			unit_x;
	int			unit_y;

	rect = (SDL_Rect){0, 0, W_WIDTH, W_HEIGHT};
	set_rect_to_screen(data, &rect, 0xff0000);
	rect = (SDL_Rect){0, 0, 0, 0};
	data->policep = data->police;
	set_write_to_screen(data, rect, 0, "DOOM");
	rect = (SDL_Rect){2 * UNITX, 7 * UNITY, 2 * UNITX, 0.75 * UNITY};
	data->policep = data->police2;
	set_write_to_screen(data, rect, 0, "CONTINUE");
	rect2 = (SDL_Rect){2 * UNITX, 8 * UNITY, 2 * UNITX, 0.75 * UNITY};
	set_write_to_screen(data, rect2, 0, "QUIT");
	draw_cursor(data, cursor, rect);
	SDL_RenderPresent(data->renderer);
}

void				w_pause(t_wolf *data)
{
	int	cursor;

	if (data->key[KP] == 0)
		return ;
	SDL_FlushEvent(SDL_KEYDOWN);
	SDL_FlushEvent(SDL_MOUSEMOTION);
	cursor = 1;
	draw_main_rect(data, cursor);
	while (data->key[KP])
	{
		SDL_PollEvent(&data->event);
		if ((data->event.key.keysym.sym == SDLK_SPACE && cursor == 1)
		|| (data->event.key.keysym.sym == SDLK_p
		&& data->event.type == SDL_KEYDOWN))
			data->key[KP] = 0;
		else if (data->event.key.keysym.sym == SDLK_SPACE && cursor == 2)
			clean_exit(data, NULL, 1);
		else if (data->event.key.keysym.sym == SDLK_UP
				|| data->event.key.keysym.sym == SDLK_DOWN)
		{
			cursor = move_cursor(data, &cursor);
			draw_main_rect(data, cursor);
		}
	}
}
