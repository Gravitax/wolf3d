/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:05:22 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:08:19 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

uint32_t		get_pixel(t_wolf *data, int si, float samplex, float sampley)
{
	int			sx;
	int			sy;
	uint8_t		*p;
	t_sprite	surface;

	surface = data->sprite[si];
	SDL_LockSurface(surface.img);
	sx = samplex * surface.img->w;
	sy = sampley * surface.img->h;
	p = (uint8_t *)surface.img->pixels + sy * surface.img->pitch
		+ sx * surface.img->format->BytesPerPixel;
	SDL_UnlockSurface(surface.img);
	return (p[2] | p[1] << 8 | p[0] << 16 | 255 << 24);
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

static void     free_surfaces(t_wolf *data)
{
    int i;

    i = SNB;
    puts("0");
    while (i--)
        if (data->sprite[i].img)
        {
            SDL_FreeSurface(data->sprite[i].img);
            printf("i: %d\n", i);
        }
    puts("1");
    if (data->screen)
        SDL_FreeSurface(data->screen);
    puts("2");
}

void            clean_exit(t_wolf *data, char *str, int token)
{
    if (data)
    {
        if (data->sdl_on)
        {
            if (data->pWindow)
                SDL_DestroyWindow(data->pWindow);
            if (data->renderer)
                SDL_DestroyRenderer(data->renderer);
            free_surfaces(data);
            SDL_Quit();
        }
        if (data->str)
            ft_strdel(&data->str);
        if (data->map.map)
            ft_memdel((void **)&data->map.map);
        if (data->object)
            lst_free(data->object);
        data = NULL;
    }
    if (str)
       ft_putendl_fd(str, 2);
    exit(token ? EXIT_SUCCESS : EXIT_FAILURE);
}
