/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:48:08 by maboye            #+#    #+#             */
/*   Updated: 2019/11/26 16:12:31 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void			draw_main_rect_go(t_wolf *data, int cursor)
{
	SDL_Rect	rect;
	SDL_Rect	rect2;
	SDL_Rect	rect_cursor;
	int			unit_x;
	int			unit_y;

	rect = (SDL_Rect){0, 0, W_WIDTH, W_HEIGHT};
	set_rect_to_screen(data, &rect, 0);
	rect = (SDL_Rect){0, 0, 0, 0};
	data->policep = data->police;
	set_write_to_screen(data, rect, 0xffffff, "GAME OVER");
	rect = (SDL_Rect){2 * UNITX, 7 * UNITY, 2 * UNITX, 0.75 * UNITY};
	data->policep = data->police2;
	set_write_to_screen(data, rect, 0xffffff, "CONTINUE");
	rect2 = (SDL_Rect){2 * UNITX, 8 * UNITY, 2 * UNITX, 0.75 * UNITY};
	set_write_to_screen(data, rect2, 0xffffff, "EXIT");
	draw_cursor(data, cursor, rect, 0xffffff);
	SDL_RenderPresent(data->renderer);
}

void			game_over(t_wolf *data)
{
	int	cursor;

	cursor = 1;
	draw_main_rect_go(data, cursor);
	while (data->key[KG])
	{
		SDL_PollEvent(&data->event);
		if ((data->event.key.keysym.sym == SDLK_SPACE && cursor == 1)
		|| (data->event.key.keysym.sym == SDLK_g
		&& data->event.type == SDL_KEYDOWN))
			data->key[KG] = 0;
		else if (data->event.key.keysym.sym == SDLK_SPACE && cursor == 2)
			clean_exit(data, NULL, 1);
		else if (data->event.key.keysym.sym == SDLK_UP
				|| data->event.key.keysym.sym == SDLK_DOWN)
		{
			cursor = move_cursor(data, &cursor);
			draw_main_rect_go(data, cursor);
		}
	}
	SDL_FlushEvent(SDL_KEYUP | SDL_KEYDOWN | SDL_MOUSEMOTION);

}
