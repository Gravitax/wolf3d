/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_monster.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 20:38:46 by bebosson          #+#    #+#             */
/*   Updated: 2019/12/04 20:28:39 by bebosson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			object_minimap(t_wolf *data, t_object *list)
{
	int			i;
	SDL_Rect	rect;

	i = 0;
	if (list == NULL)
		return ;
	data->rect->h /= 4 ; 
	data->rect->w /= 4 ; 
	while (list)
	{
		if (list->type > 2 && list->type < 10)
		{
			data->rect->x = list->x * W_WIDTH / (data->map.sc_x * data->map.width);
			data->rect->y = list->y * W_HEIGHT / (data->map.sc_x * data->map.height);
			set_rect_to_screen(data, data->rect, 0);
			SDL_RenderFillRect(data->renderer, data->rect);
		}
		list = list->next;
		i++;
	}
}

void			draw_fps(t_wolf *data)
{
	char		*fps;

	fps = ft_strfjoin("fps ", ft_itoa(data->fps), 2);
	(*(data->rect)) = (SDL_Rect){0, W_HEIGHT / data->map.sc_x - 5,
		10 * data->map.sc_x, 3 * data->map.sc_x};
	data->policep = data->police3;
	set_write_to_screen(data, (*(data->rect)), 0, fps);
	ft_strdel(&fps);
}

t_wolf 	*minimap_alloc(t_wolf *data)
{
	if (!(data->rect = malloc(sizeof(SDL_Rect))))
		return (0);
	if (!(data->pl = malloc(sizeof(SDL_Point))))
		return (0);
	if (!(data->point = (SDL_Point *)ft_memalloc(sizeof(SDL_Point) * 2)))
		return (0);	
	return (data);
}
