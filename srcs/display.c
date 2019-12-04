/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/12/04 18:05:44 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		textures(t_wolf *data)
{
	int				i;
	unsigned int	*pixels;
	SDL_Rect		rect;

	//skybox(data);
	rect.h = W_HEIGHT / 2;
	rect.w = W_WIDTH;
	rect.x = 0;
	rect.y = W_HEIGHT / 2;
	SDL_RenderCopy(data->renderer, data->bgf, NULL, &rect);
	rect.h = W_HEIGHT;
	rect.y = 0;
	SDL_LockSurface(data->screen);
	data->window = SDL_CreateTextureFromSurface(data->renderer, data->screen);
	SDL_RenderCopy(data->renderer, data->window, NULL, &rect);
	pixels = (unsigned int *)data->screen->pixels;
	i = -1;
	while (++i < W_WIDTH * W_HEIGHT)
		pixels[i] = 0x000000;
	SDL_UnlockSurface(data->screen);
}

static void		cursor(t_wolf *data)
{
	SDL_SetRenderDrawColor(data->renderer, 255, 0, 0, 100);
	SDL_RenderDrawLine(data->renderer,
			W_WIDTH / 2 - 15, W_HEIGHT / 2,
			W_WIDTH / 2 + 15, W_HEIGHT / 2);
	SDL_RenderDrawLine(data->renderer,
			W_WIDTH / 2, W_HEIGHT / 2 - 15,
			W_WIDTH / 2, W_HEIGHT / 2 + 15);
	SDL_RenderDrawLine(data->renderer,
			W_WIDTH / 2 - 15, W_HEIGHT / 2 - 1,
			W_WIDTH / 2 + 15, W_HEIGHT / 2 - 1);
	SDL_RenderDrawLine(data->renderer,
			W_WIDTH / 2 - 1, W_HEIGHT / 2 - 15,
			W_WIDTH / 2 - 1, W_HEIGHT / 2 + 15);
	SDL_RenderDrawLine(data->renderer,
			W_WIDTH / 2 - 15, W_HEIGHT / 2 + 1,
			W_WIDTH / 2 + 15, W_HEIGHT / 2 + 1);
	SDL_RenderDrawLine(data->renderer,
			W_WIDTH / 2 + 1, W_HEIGHT / 2 - 15,
			W_WIDTH / 2 + 1, W_HEIGHT / 2 + 15);
}

static void		health_color(t_wolf *data, int ratio)
{
	if (data->player.health > 0)
		SDL_SetRenderDrawColor(data->renderer, 255, 0, 0, 100);
	if (data->player.health > ratio * 20)
		SDL_SetRenderDrawColor(data->renderer, 255, 165, 0, 100);
	if (data->player.health > ratio * 40)
		SDL_SetRenderDrawColor(data->renderer, 255, 255, 0, 100);
	if (data->player.health > ratio * 60)
		SDL_SetRenderDrawColor(data->renderer, 50, 200, 35, 0);
	if (data->player.health > ratio * 80)
		SDL_SetRenderDrawColor(data->renderer, 30, 150, 0, 100);
}

static void		health(t_wolf *data)
{
	int			p;
	int			ratio;
	SDL_Rect	rect;

	ratio = data->player.health_max / 100;
	SDL_SetRenderDrawColor(data->renderer, 0, 0, 0, 100);
	rect.x = 10;
	rect.y = W_HEIGHT / 8 * 7;
	rect.h = W_HEIGHT / 10;
	rect.w = W_WIDTH / 4;
	SDL_RenderFillRect(data->renderer, &rect);
	p = 2;
	rect.x = 10 + p;
	rect.y = W_HEIGHT / 8 * 7 + p;
	rect.h = W_HEIGHT / 10 - p * 2;
	rect.w = ((W_WIDTH / 4) / 100) * (data->player.health / ratio) - p * 2;
	health_color(data, ratio);
	SDL_RenderFillRect(data->renderer, &rect);
}

void			display(t_wolf *data)
{
	if (data->player.angle >= 6.3f)
		data->player.angle = 0;
	else if (data->player.angle < 0)
		data->player.angle = 6.3f;
	raycasting(data);
	monsters(data);
	objects(data, data->object);
	weapons(data);
	textures(data);
	cursor(data);
	health(data);
	if (data->key[KM])
		minimap(data);
	SDL_RenderPresent(data->renderer);
	SDL_DestroyTexture(data->window);
}
