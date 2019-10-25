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

void			draw_pixel(t_wolf *data, int i, float x, float y)
{
	int			sx;
	int			sy;
	uint8_t		*p;
	t_surface	surface;

	surface = data->surface[i];
	SDL_LockSurface(surface.img);
	sx = x * surface.img->w;
	sy = y * surface.img->h;
	p = (uint8_t *)surface.img->pixels + sy * surface.img->pitch
		+ sx * surface.img->format->BytesPerPixel;
	SDL_UnlockSurface(surface.img);
	SDL_SetRenderDrawColor(data->renderer, p[2], p[1], p[0], 100);
}

void			draw_ray(t_wolf *data, int x, float samplex, float dst_towall)
{
	int			ceiling = W_HEIGTH / 2 - W_HEIGTH / dst_towall;
	int			floor = W_HEIGTH - ceiling;
	float		sampley = 0;

	(void)samplex;
	(void)sampley;

	for (int y = 0; y < W_HEIGTH; y++)
	{
		if (y <= ceiling)
		{
			// sampley = ((float)y)  / ((float)ceiling);
			// draw_pixel(data, 7, samplex, sampley);

			SDL_SetRenderDrawColor(data->renderer, 0, 0, 0, 100);
		}
		else if (y > ceiling && y <= floor)
		{
			if (dst_towall < data->map.depth)
			{
				// sampley = ((float)y - (float)ceiling) / ((float)floor - (float)ceiling);
				// draw_pixel(data, data->si, samplex, sampley);

				SDL_SetRenderDrawColor(data->renderer, 0, 0, 100, 100);
			}
			else
				SDL_SetRenderDrawColor(data->renderer, 0, 0, 0, 100);
		}
		else
		{
			// float	b = (((float)y - W_HEIGTH / 2) / ((float)W_HEIGTH / 2));
			// SDL_SetRenderDrawColor(data->renderer, 200 * b, 200 * b, 200 * b, 100);

			// samplex = ((float)x) / (float)floor;
			// sampley = ((float)y - (float)floor) / ((float)floor);
			// draw_pixel(data, 6, samplex, sampley);
			
			SDL_SetRenderDrawColor(data->renderer, 100, 0, 0, 100);
		}
		SDL_RenderDrawPoint(data->renderer, x, y);
	}
}

void			*raycasting(void *d)
{
	t_wolf		*data = (t_wolf *)d;
	float		fov = data->player.fov;
	float		samplex = 0;

	while (data->x < data->x_max)
	{
		//printf("x: %d, xmax: %d\n", data->x, data->x_max);
		float	ray_angle = (data->player.angle - fov / 2)
			+ ((float)data->x / (float)W_WIDTH) * fov;

		float	dst_towall = 0;
		int		hitwall = 0;

		float	eyex = cosf(ray_angle);
		float	eyey = sinf(ray_angle);
		while (!hitwall && dst_towall < data->map.depth)
		{
			dst_towall += data->ray_step;
			int	testx = (int)(data->player.x + eyex * dst_towall);
			int	testy = (int)(data->player.y + eyey * dst_towall);
			if (testx < 0 || testx >= data->map.width
				|| testy < 0 || testy >= data->map.height)
			{
				hitwall = 1;
				dst_towall = data->map.depth;
			}
			else
			{
				if (data->map.map[testy * data->map.width + testx] == 1)
				{
					hitwall = 1;

					// float	blockmidx = (float)testx + 0.5;
					// float	blockmidy = (float)testy + 0.5;

					// float	testpointx = data->player.x + eyex * dst_towall;
					// float	testpointy = data->player.y + eyey * dst_towall;
					// float	testangle = atan2f((testpointy - blockmidy), (testpointx - blockmidx));

					// samplex = (float)testy - testpointy;
					// if (testangle >= -3.14159 * 0.25 && testangle < 3.14159 * 0.25)
					// {
					// 	samplex = (float)testy - testpointy;
					// 	data->si = 1;
					// }
					// else if (testangle >= 3.14159 * 0.25 && testangle < 3.14159 * 0.75)
					// {
					// 	samplex = testpointx - (float)testx;
					// 	data->si = 2;
					// }
					// else if (testangle < -3.14159 * 0.25 && testangle >= -3.14159 * 0.75)
					// {
					// 	samplex = (float)testx - testpointx;
					// 	data->si = 3;
					// }
					// else if (testangle >= -3.14159 * 0.75 || testangle < -3.14159 * 0.75)
					// {
					// 	samplex = testpointy - (float)testy;
					// 	data->si = 4;
					// }
				}	
			}
		}
		draw_ray(data, data->x, samplex, dst_towall);
		++data->x;
	}
	return (d);
}
