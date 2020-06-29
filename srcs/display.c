/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/12/04 20:18:39 by bebosson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			display(t_wolf *data)
{
	if (data->player.angle >= 6.3f)
		data->player.angle = 0;
	else if (data->player.angle < 0)
		data->player.angle = 6.3f;
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
}
