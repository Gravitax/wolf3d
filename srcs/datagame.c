/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datagame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/11/29 17:04:14 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		get_list(t_wolf *data, t_object *list, int min, int max)
{
	t_object	*head;
	int			i;

	if (list == NULL)
		return ;
	head = list;
	i = -1;
	while (++i < data->map.len)
		if (data->map.map[i] >= min && data->map.map[i] <= max)
		{
			list->y = i / data->map.width;
			list->x = i - (list->y * data->map.width) + 1;
			list->type = data->map.map[i];
			list->hp = get_objhp(data, list);
			list->hp_max = list->hp;
			list->speed = 0.2f;
			list->si = list->type;
			list->i = list->x + data->map.width * list->y;
			list->sprite = data->sprite[list->si];
			lst_pushback(list, (t_object *)ft_memalloc(sizeof(t_object)));
			if (list == NULL)
				clean_exit(data, "wolf3d: malloc error", 0);
			list = list->next;
		}
	list = head;
}

static void		background(t_wolf *data)
{
	SDL_LockSurface(data->sprite[0].img);
	if (!(data->bgc = SDL_CreateTextureFromSurface(data->renderer,
					data->sprite[0].img)))
		clean_exit(data, "wolf3d: SDL_CreateTextures fail", 0);
	SDL_UnlockSurface(data->sprite[0].img);
	SDL_LockSurface(data->sprite[1].img);
	if (!(data->bgf = SDL_CreateTextureFromSurface(data->renderer,
					data->sprite[1].img)))
		clean_exit(data, "wolf3d: SDL_CreateTextures fail", 0);
	SDL_UnlockSurface(data->sprite[1].img);
}

static void		weapons_data(t_wolf *data)
{
	data->player.wdata[0].damage = 60;
	data->player.wdata[0].delay = 40;
	data->player.wdata[0].range = 4;
	data->player.wdata[0].si = 20;
	data->player.wdata[1].damage = 30;
	data->player.wdata[1].delay = 15;
	data->player.wdata[1].range = data->map.depth;
	data->player.wdata[1].si = 22;
	data->player.wdata[2].damage = 180;
	data->player.wdata[2].delay = 60;
	data->player.wdata[2].range = data->map.depth;
	data->player.wdata[2].si = 24;
	data->player.wdata[3].damage = 40;
	data->player.wdata[3].delay = 5;
	data->player.wdata[3].range = data->map.depth;
	data->player.wdata[3].si = 26;
}

void			load_datagame(t_wolf *data)
{
	SDL_GetWindowPosition(data->pwindow, &data->wx, &data->wy);
	sprites(data);
	if (!(data->object = (t_object *)ft_memalloc(sizeof(t_object))))
		clean_exit(data, "wolf3d: malloc error", 0);
	if (!(data->monster = (t_object *)ft_memalloc(sizeof(t_object))))
		clean_exit(data, "wolf3d: malloc error", 0);
	get_list(data, data->object, 3, 5);
	get_list(data, data->monster, 6, 9);
	background(data);
	if (!(data->screen = new_surface(W_WIDTH, W_HEIGHT)))
		clean_exit(data, "wolf3d: error creating RGB surface", 0);
	get_nodes(data);
	weapons_data(data);
}
