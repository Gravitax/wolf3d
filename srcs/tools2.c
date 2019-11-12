/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:05:22 by maboye            #+#    #+#             */
/*   Updated: 2019/11/05 13:20:11 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

float           distance(float x1, float y1, float x2, float y2)
{
	return (ft_sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
    //return (Q_sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

float			Q_sqrt(float number)
{
	long 		i;
	float 		x2;
	float		y;
	const float	threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = *(long *)&y;			// evil floating point bit level hacking
	i  = 0x5f3759df - (i >> 1);	// what the fuck? 
	y  = *(float *)&i;
	y  = y * (threehalfs - (x2 * y * y));
	return (1 / y);
}

uint32_t		get_pixel(t_wolf *data, int si, float samplex, float sampley)
{
	int				sx;
	int				sy;
	uint8_t			*p;
	uint32_t		pixel;
	t_sprite		surface;

	surface = data->sprite[si];
	SDL_LockSurface(surface.img);
	sx = samplex * surface.img->w;
	sy = sampley * surface.img->h;
	p = (uint8_t *)surface.img->pixels + sy * surface.img->pitch
		+ sx * surface.img->format->BytesPerPixel;
	pixel = (p[2] | p[1] << 8 | p[0] << 16 | 255 << 24);
	//pixel = (p[0] | p[1] << 8 | p[2] << 16 | 255 << 24);
	SDL_UnlockSurface(surface.img);
	return (pixel);
}

SDL_Surface     *new_surface(int w, int h)
{
	Uint32			color[4];

	color[0] = 0x000000ff;
	color[1] = 0x0000ff00;
	color[2] = 0x00ff0000;
	color[3] = 0xff000000;
	return (SDL_CreateRGBSurface(0, w, h, 32,
        color[0], color[1], color[2], color[3]));
}

void		    put_pixel(SDL_Surface *surface, int x, int y, uint32_t color)
{
	unsigned int	*pixels;
	
	if (x < 0 || x > W_WIDTH || y < 0 || y > W_HEIGHT)
		return ;
	SDL_LockSurface(surface);
	pixels = (unsigned int *)surface->pixels;
	pixels[x + (y * W_WIDTH)] = color;
	SDL_UnlockSurface(surface);
}