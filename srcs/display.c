/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/12/12 23:07:37 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		remove_objects(t_wolf *data)
{
	t_object	*tmp;
	t_object	*head;

	head = data->object;
	while (data->object && data->object->dead == 1)
	{
		data->pfdata.list[data->object->i].bobstacle = 0;
		tmp = data->object->next;
		ft_memdel((void **)&data->object);
		data->object = tmp;
		head = data->object;
	}
	while (data->object)
	{
		tmp = data->object;
		data->object = data->object->next;
		while (data->object && data->object->dead == 1)
		{
			data->pfdata.list[data->object->i].bobstacle = 0;
			tmp->next = data->object->next;
			ft_memdel((void **)&data->object);
			data->object = tmp->next;
		}
	}
	data->object = head;
}

static void		textures(t_wolf *data)
{
	int				i;
	unsigned int	*pixels;
	SDL_Rect		rect;

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

void			get_fps(t_wolf *d)
{
	d->oldtime = d->time;
	d->time = SDL_GetTicks();
	d->frametime = (d->time - d->oldtime) / 1000.0;
	d->fps = 1.0 / d->frametime;
	d->mv_speed = d->frametime * 5.0;
	d->rot_speed = d->frametime * 3.0;
}

void			display(t_wolf *data)
{
	raycasting(data);
	monsters(data);
	objects(data, data->monster);
	objects(data, data->object);
	remove_objects(data);
	weapons(data);
	textures(data);
	cursor(data);
	health(data);
	if (data->key[KM])
		minimap(data);
	SDL_RenderPresent(data->renderer);
	SDL_DestroyTexture(data->window);
	get_fps(data);
}
