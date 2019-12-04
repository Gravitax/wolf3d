/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/12/02 17:38:59 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			skybox(t_wolf *data)
{
	int			width;
	float		ratio;
	float		ratio2;
	SDL_Rect	rect;

	width = data->sprite[0].img->w;
	ratio = width / 6.3f;
	rect.h = W_HEIGHT / 2;
	rect.w = width;
	rect.x = -(data->player.angle * ratio);
	rect.y = 0;
	SDL_RenderCopy(data->renderer, data->bgc, NULL, &rect);
	rect.x = -(data->player.angle * ratio - width);
	SDL_RenderCopy(data->renderer, data->bgc, NULL, &rect);
}
