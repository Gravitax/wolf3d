/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebosson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:33:16 by bebosson          #+#    #+#             */
/*   Updated: 2019/11/14 22:41:15 by bebosson         ###   ########.fr       */
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

static int mouse_rect(t_wolf *data, SDL_Rect rect2, SDL_Rect rect3)
{
	if ((data->event.motion.x >= rect2.x && data->event.motion.x <= rect2.x + rect2.w)
		   && (data->event.motion.y	>= rect2.y && data->event.motion.y <= (rect2.y + rect2.h)))
				return (1);
	if ((data->event.motion.x >= rect3.x && data->event.motion.x <= rect3.x + rect3.w)
		   && (data->event.motion.y	>= rect3.y && data->event.motion.y <= (rect3.y + rect3.h)))
				return (2);
	else
		return (0);
}


static void	draw_mouse(t_wolf *data, SDL_Rect rect2, SDL_Rect rect3)
{
	SDL_Point		mouse;

//	SDL_RenderDrawLine(data->renderer, data->event.motion.x - 15, data->event.motion.y, data->event.motion.x + 15, data->event.motion.y);
//	SDL_RenderDrawLine(data->renderer, data->event.motion.x, data->event.motion.y - 15, data->event.motion.x, data->event.motion.y + 15);
	if (data->event.button.clicks == 1)
	{
		if (mouse_rect(data, rect2, rect3) == 1)
			clean_exit(data, NULL, 1);
		if (mouse_rect(data, rect2, rect3) == 2)
			data->key[KP] = 0;	
	}
}
static void	draw_pause_submenu_exit(t_wolf *data, SDL_Rect rect, SDL_Rect *rect2)
{
	int			texW;
	int			texH;
	SDL_Surface *surface;
	SDL_Texture * texture;
	//police 

	//bg
	rect.x = 0;
	rect.y = 0;
	rect.w = W_WIDTH;
	rect.h = W_HEIGHT;
	SDL_SetRenderDrawColor(data->renderer, 139, 0, 0, 0);
	SDL_RenderFillRect(data->renderer, &rect);
	surface = TTF_RenderText_Solid(data->police, "pause !", ft_hex_to_rgb(0x0000ff));
	texture = SDL_CreateTextureFromSurface(data->renderer, surface);
//	SDL_RenderCopy(data->renderer, texture, NULL, NULL);
	texW = 50;
	texH = 50;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { 0, 0, texW, texH };
	SDL_RenderCopy(data->renderer, texture, NULL, &dstrect);
	//    SDL_LockSurface(data->screen);
/*
	unit_x = W_WIDTH/16;
   	unit_y = W_HEIGHT/10;	
	(*rect2).x = 2 * unit_x;
	(*rect2).y = 6 * unit_y;
	(*rect2).w = 2 * unit_x;
	(*rect2).h = 0.75 * unit_y;
*/
	// recup pour l'action mouse 
//	SDL_SetRenderDrawColor(data->renderer, 100, 0, 0, 100);
//	SDL_RenderFillRect(data->renderer, rect2);
   
   	//SDL_UnlockSurface(data->screen);

//	SDL_RenderPresent(data->renderer);
//	SDL_RenderFillRect(data->renderer, &rect);
}

static void	draw_pause_submenu_resume(t_wolf *data, SDL_Rect *rect3)
{
	int			unit_x;
	int			unit_y;
	
	//fg
	unit_x = W_WIDTH/16;
   	unit_y = W_HEIGHT/10;	
	(*rect3).x = 2 * unit_x;
	(*rect3).y = 7.5 * unit_y;
	(*rect3).w = 12 * unit_x;
	(*rect3).h = 0.75 * unit_y;
	// recup pour l'action mouse 
	SDL_SetRenderDrawColor(data->renderer, 192, 192, 192, 100);
	SDL_RenderFillRect(data->renderer, rect3);
}

void	w_pause(t_wolf *data)
{
	SDL_Rect	rect; //bg
	SDL_Rect	rect2; //quit programme (fg)
	SDL_Rect	rect3; // resume game

	while (data->key[KP])
	{
		SDL_PollEvent(&data->event);
		if (data->event.key.keysym.sym == SDLK_p)
		{
			if (data->event.type == SDL_KEYDOWN)
				data->key[KP] = 0;
		}
		draw_pause_submenu_exit(data, rect, &rect2);
		draw_pause_submenu_resume(data, &rect3);
		draw_mouse(data, rect2, rect3);
    	SDL_RenderPresent(data->renderer);
	}
}
