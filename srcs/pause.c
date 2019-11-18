/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebosson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:33:16 by bebosson          #+#    #+#             */
/*   Updated: 2019/11/18 19:39:26 by bebosson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//square position ;
#include "../includes/wolf3d.h"

static SDL_Color		ft_hex_to_rgb(int hexa)
{
	SDL_Color color;

	color.r = hexa >> 24;
	color.g = hexa >> 16;
	color.b = hexa >> 8;
	color.a = hexa;
	return (color);
}

static int mouse_rect(t_wolf *data, SDL_Rect rect)
{
	if ((data->event.motion.x >= rect.x && data->event.motion.x <= rect.x + rect.w)
		   && (data->event.motion.y	>= rect.y && data->event.motion.y <= (rect.y + rect.h)))
				return (1);
	else
		return (0);
}

/*
static void	draw_mouse(t_wolf *data, SDL_Rect rect2, SDL_Rect rect3)
{
	SDL_Point		mouse;

	if (data->event.button.clicks == 1)
	{
		if (mouse_rect(data, rect2, rect3) == 1)
			clean_exit(data, NULL, 1);
		if (mouse_rect(data, rect2, rect3) == 2)
			data->key[KP] = 0;	
	}
}
*/
void	set_write_to_screen(t_wolf *data, SDL_Rect rect, int color, char *str, TTF_Font *pl)
{
	SDL_Surface *surface;
	SDL_Texture * texture;
	//police 

	//bg
	SDL_SetRenderDrawColor(data->renderer, (color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff, 0);
	surface = TTF_RenderText_Solid(pl, str, ft_hex_to_rgb(color));
	texture = SDL_CreateTextureFromSurface(data->renderer, surface);
	SDL_QueryTexture(texture, 0, 0, &(rect.w), &(rect.h));
	SDL_RenderCopy(data->renderer, texture, NULL, &rect);
}

static void	set_rect_to_screen(t_wolf *data, SDL_Rect *rect, int color)
{
	SDL_SetRenderDrawColor(data->renderer, (color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff, 100);
	SDL_RenderFillRect(data->renderer, rect);
}
/*
		unit_x = W_WIDTH/16;
   	unit_y = W_HEIGHT/10;	
	(*rect3).x = 2 * unit_x;
	(*rect3).y = 7.5 * unit_y;
	(*rect3).w = 12 * unit_x;
	(*rect3).h = 0.75 * unit_y;

    unit_x = W_WIDTH/16;
   	unit_y = W_HEIGHT/10;	
	(*rect2).x = 2 * unit_x;
	(*rect2).y = 6 * unit_y;
	(*rect2).w = 2 * unit_x;
	(*rect2).h = 0.75 * unit_y;
*/

static int		move_cursor(t_wolf *data, int cursor)
{
	if (data->event.key.keysym.sym == SDLK_UP && cursor > 1)	// move rect_cursor depends on value of cursor
		return (--cursor);
	else if (data->event.key.keysym.sym == SDLK_DOWN && cursor < 2)	// move rect_cursor depends on value of cursor
		return (++cursor);
	else
		return (cursor);
}

void	draw_cursor(t_wolf *data, int cursor, SDL_Rect rect)
{
	SDL_Rect	rect_cursor;
	int			unit_x;
	int			unit_y;

	unit_x = W_WIDTH/16;
   	unit_y = W_HEIGHT/10;
	printf("cursor = %d\n",cursor);
	rect_cursor = (SDL_Rect){12 * unit_x, (6 + cursor) * unit_y, unit_x/2, unit_y/2};
	set_rect_to_screen(data, &rect_cursor, 0);
	if (cursor == 1 && data->event.type == SDLK_SPACE)
		data->key[KP] = 0;
	else if (cursor == 2 && data->event.type == SDLK_SPACE)
 		clean_exit(data, NULL, 1);

}

void	w_pause(t_wolf *data)
{
	SDL_Rect	rect;
	SDL_Rect	rect2;
	int			unit_x;
	int			unit_y;
	int			cursor;

	unit_x = W_WIDTH/16;
   	unit_y = W_HEIGHT/10;
	cursor = 1;	
	while (data->key[KP])
	{
		SDL_PollEvent(&data->event);
		
		rect = (SDL_Rect){0, 0, W_WIDTH, W_HEIGHT};
		set_rect_to_screen(data, &rect, 0xff0000);
		rect = (SDL_Rect){0, 0, 0, 0};
		set_write_to_screen(data, rect, 0x000000, "DOOM", data->police);
		rect = (SDL_Rect){2 * unit_x, 7 * unit_y, 2 * unit_x, 0.75 * unit_y};
		set_write_to_screen(data, rect, 0x000000, "START", data->police2);
		rect2 = (SDL_Rect){2 * unit_x, 8 * unit_y, 2 * unit_x, 0.75 * unit_y};
		set_write_to_screen(data, rect2, 0x000000, "QUIT", data->police2);
		draw_cursor(data, cursor, rect);	
    	SDL_RenderPresent(data->renderer);
		if (data->event.key.keysym.sym == SDLK_p || data->event.key.keysym.sym == SDLK_ESCAPE || data->event.key.keysym.sym == SDLK_SPACE)
		{
			if ((data->event.type == SDL_KEYDOWN || mouse_rect(data, rect) == 1) || ( data->event.key.keysym.sym == SDLK_SPACE && cursor == 1))
				data->key[KP] = 0;
			if (data->event.type == SDL_QUIT || mouse_rect(data, rect2) == 1 || ( data->event.key.keysym.sym == SDLK_SPACE && cursor == 2))
        		clean_exit(data, NULL, 1);
		}
		else if (data->event.key.keysym.sym == SDLK_UP || data->event.key.keysym.sym == SDLK_DOWN)
			cursor = move_cursor(data, cursor);


//		draw_mouse(data, rect2, rect3);
//    	SDL_RenderPresent(data->renderer);
	}
}
