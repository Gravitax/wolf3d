/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:05:22 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:08:19 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			raycasting(t_wolf *data)
{
	float	fov = 3.14159 / 4;

	float	depth = data->map.depth;

	for (int x = 0; x < W_WIDTH; x++)
	{
		float	ray_angle = (data->player.angle - fov / 2)
			+ ((float)x / (float)W_WIDTH) * fov;

		float	dst_towall = 0;
		int		hitwall = 0;

		float	eyex = cosf(ray_angle);
		float	eyey = sinf(ray_angle);
		while (!hitwall && dst_towall < depth)
		{
			dst_towall += 0.1;
			int	testx = (int)(data->player.x + eyex * dst_towall);
			int	testy = (int)(data->player.y + eyey * dst_towall);
			if (testx < 0 || testx >= data->map.width
				|| testy < 0 || testy >= data->map.height)
			{
				hitwall = 1;
				dst_towall = depth;
			}
			else
			{
				if (data->map.map[testy * data->map.width
					+ testx] == 1)
				{
					hitwall = 1;
				}	
			}
		}

		int	ceiling = (float)(W_HEIGTH / 2.0)
			- W_HEIGTH / ((float)dst_towall);
		int	floor = W_HEIGTH - ceiling;

		for (int y = 0; y < W_HEIGTH; y++)
		{
			SDL_SetRenderDrawColor(data->renderer, 0, 0, 0, 100);
			if (y < ceiling)
				SDL_RenderDrawPoint(data->renderer, x, y);
			else if (y > ceiling && y <= floor)
			{
				if (dst_towall <= depth / 4)
					SDL_SetRenderDrawColor(data->renderer, 200, 0, 200, 100);
				else if (dst_towall <= depth / 3)
					SDL_SetRenderDrawColor(data->renderer, 150, 0, 150, 100);
				else if (dst_towall <= depth / 2)
					SDL_SetRenderDrawColor(data->renderer, 100, 0, 100, 100);
				else if (dst_towall < depth)
					SDL_SetRenderDrawColor(data->renderer, 50, 0, 50, 100);
				else
					SDL_SetRenderDrawColor(data->renderer, 0, 0, 0, 100);
				SDL_RenderDrawPoint(data->renderer, x, y);
			}
			else
			{
				float	b = 1 - (((float)y - W_HEIGTH / 2)
					/ ((float)W_HEIGTH / 2));
				if (b < 0.25)
					SDL_SetRenderDrawColor(data->renderer, 200, 200, 200, 100);
				else if (b < 0.5)
					SDL_SetRenderDrawColor(data->renderer, 150, 150, 150, 100);
				else if (b < 0.75)
					SDL_SetRenderDrawColor(data->renderer, 100, 100, 100, 100);
				else if (b < 0.9)
					SDL_SetRenderDrawColor(data->renderer, 50, 50, 50, 100);
				else
					SDL_SetRenderDrawColor(data->renderer, 0, 0, 0, 100);
				SDL_RenderDrawPoint(data->renderer, x, y);
			}
		}
	}
}
