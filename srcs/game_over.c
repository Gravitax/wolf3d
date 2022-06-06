/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:48:08 by maboye            #+#    #+#             */
/*   Updated: 2022/06/06 16:50:41 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static int			move_cursor(t_wolf *data, int *cursor)
{
	if (data->event.key.keysym.sym == SDLK_UP && *cursor > 1)
		return (--*cursor);
	else if (data->event.key.keysym.sym == SDLK_DOWN && *cursor < 2)
		return (++*cursor);
	else
		return (*cursor);
}

static void			draw_cursor(t_wolf *data, int cursor)
{
	int			x;

	x = 7;
	while (x < 11)
	{
		(*(data->rect)) = (SDL_Rect){x * UNITX, (6.5 + cursor)
			* UNITY, UNITX / 6, UNITY / 6};
		set_rect_to_screen(data, data->rect, 0);
		x++;
	}
	(*(data->rect)) = (SDL_Rect){x * UNITX, (6 + cursor)
		* UNITY, UNITX / 2, UNITY / 2};
	set_rect_to_screen(data, data->rect, 0);
}

static void			draw_main_rect(t_wolf *data, int cursor)
{
	(*(data->rect)) = (SDL_Rect){0, 0, W_WIDTH, W_HEIGHT};
	set_rect_to_screen(data, data->rect, 0xff0000);
	(*(data->rect)) = (SDL_Rect){0, 0, 0, 0};
	// data->policep = data->police;
	set_write_to_screen(data, (*(data->rect)), 0, "GAME OVER");
	(*(data->rect)) = (SDL_Rect){2 * UNITX, 7 * UNITY, 2 * UNITX, 0.75 * UNITY};
	// data->policep = data->police2;
	set_write_to_screen(data, (*(data->rect)), 0, "CONTINUE");
	(*(data->rect)) = (SDL_Rect){2 * UNITX, 8 * UNITY, 2 * UNITX, 0.75 * UNITY};
	set_write_to_screen(data, (*(data->rect)), 0, "QUIT");
	draw_cursor(data, cursor);
	SDL_RenderPresent(data->renderer);
}

void				game_over(t_wolf *data)
{
	int	cursor;

	cursor = 1;
	SDL_FlushEvent(SDL_KEYDOWN);
	SDL_FlushEvent(SDL_MOUSEMOTION);
	draw_main_rect(data, cursor);
	while (data->player.health < 1)
	{
		SDL_PollEvent(&data->event);
		if (data->event.key.keysym.sym == SDLK_SPACE && cursor == 1)
			data->player.health = 200;
		else if ((data->event.key.keysym.sym == SDLK_SPACE && cursor == 2)
				|| data->event.key.keysym.sym == SDLK_ESCAPE
				|| data->event.key.keysym.sym == SDL_QUIT)
			clean_exit(data, NULL, 1);
		else if (data->event.key.keysym.sym == SDLK_UP
				|| data->event.key.keysym.sym == SDLK_DOWN)
		{
			cursor = move_cursor(data, &cursor);
			draw_main_rect(data, cursor);
		}
	}
}
