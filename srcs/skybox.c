/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/11/28 12:34:41 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			skybox(t_wolf *data)
{
	int			width;
	float		ratio;
	SDL_Rect	rect;

	width = data->sprite[0].img->w;
	ratio = width / 6;
	rect.h = W_HEIGHT / 2;
	rect.w = width;
	rect.x = -(data->player.angle * ratio);
	rect.y = 0;
	SDL_RenderCopy(data->renderer, data->bgc, NULL, &rect);
	rect.x = -(data->player.angle * ratio - width);
	SDL_RenderCopy(data->renderer, data->bgc, NULL, &rect);
}
