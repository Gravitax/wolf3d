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

void			drawpixel(t_wolf *data, int i, float x, float y)
{
	int			sx;
	int			sy;
	uint8_t		*p;
	uint32_t	pixel;
	t_surface	surface;

	surface = data->surface[i];
	SDL_LockSurface(surface.img);
	sx = x * surface.img->w;
	sy = y * surface.img->h;
	p = (uint8_t *)surface.img->pixels + sy
		* surface.img->pitch + sx * surface.img->format->BytesPerPixel;
	pixel = p[0] | p[1] << 8 | p[2] << 16;
	SDL_GetRGB(pixel, surface.img->format ,  &surface.r, &surface.g, &surface.b);
	SDL_UnlockSurface(surface.img);
	SDL_SetRenderDrawColor(data->renderer, surface.r, surface.g, surface.b, 100);
}

void			raycasting(t_wolf *data)
{
	float	fov = 3.14159 / 4;
	float	depth = data->map.depth / 2;
	float	samplex = 0;
	float	sampley = 0;
	int		surface = 0;

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
			dst_towall += data->ray_step;
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
				if (data->map.map[testy * data->map.width + testx] == 1)
				{
					hitwall = 1;

					float	blockmidx = (float)testx + 0.5;
					float	blockmidy = (float)testy + 0.5;

					float	testpointx = data->player.x + eyex * dst_towall;
					float	testpointy = data->player.y + eyey * dst_towall;
					float	testangle = atan2f((testpointy - blockmidy), (testpointx - blockmidx));

					if (testangle >= -3.14159 * 0.25 && testangle < 3.14159 * 0.25)
					{
						samplex = (float)testy - testpointy;
						surface = 1;
					}
					else if (testangle >= 3.14159 * 0.25 && testangle < 3.14159 * 0.75)
					{
						samplex = testpointx - (float)testx;
						surface = 2;
					}
					else if (testangle < -3.14159 * 0.25 && testangle >= -3.14159 * 0.75)
					{
						samplex = (float)testx - testpointx;
						surface = 3;
					}
					else if (testangle >= -3.14159 * 0.75 || testangle < -3.14159 * 0.75)
					{
						samplex = testpointy - (float)testy;
						surface = 4;
					}
				}	
			}
		}

		int	ceiling = W_HEIGTH / 2 - W_HEIGTH / dst_towall;
		int	floor = W_HEIGTH - ceiling;

		for (int y = 0; y < W_HEIGTH; y++)
		{
			if (y <= ceiling)
				SDL_SetRenderDrawColor(data->renderer, 0, 0, 0, 100);
			else if (y > ceiling && y <= floor)
			{
				if (dst_towall < depth)
				{
					sampley = ((float)y - (float)ceiling) / ((float)floor - (float)ceiling);
					drawpixel(data, surface, samplex, sampley);
				}
				else
					SDL_SetRenderDrawColor(data->renderer, 0, 0, 0, 100);
			}
			else
			{
				float	b = (((float)y - W_HEIGTH / 2) / ((float)W_HEIGTH / 2));
				SDL_SetRenderDrawColor(data->renderer, 200 * b, 200 * b, 200 * b, 100);

				// sampley = ((float)y - (float)floor) / ((float)floor);
				// drawpixel(data, 0, samplex, sampley);
			}
			SDL_RenderDrawPoint(data->renderer, x, y);
		}
	}
}
