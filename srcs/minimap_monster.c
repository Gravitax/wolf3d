/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_monster.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 20:38:46 by bebosson          #+#    #+#             */
/*   Updated: 2019/11/26 17:57:08 by maboye           ###   ########.fr       */
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
	rect.h = W_HEIGHT / (data->map.sc_x * 2 * data->map.height);
	rect.w = W_WIDTH / (data->map.sc_x * 2 * data->map.width);
	while (list)
	{
		if (list->type > 2 && list->type < 10)
		{
			rect.x = list->x * W_WIDTH / (data->map.sc_x * data->map.width);
			rect.y = list->y * W_HEIGHT / (data->map.sc_x * data->map.height);
			set_rect_to_screen(data, &rect, 0);
		}
		list = list->next;
		i++;
	}
}

void			draw_fps(t_wolf *data)
{
	SDL_Rect	rect;
	char		*fps;

	fps = ft_strfjoin("fps ", ft_itoa(data->fps), 2);
	rect = (SDL_Rect){0, W_HEIGHT / data->map.sc_x - 5,
		10 * data->map.sc_x, 3 * data->map.sc_x};
	data->policep = data->police3;
	set_write_to_screen(data, rect, 0, fps);
	ft_strdel(&fps);
}
