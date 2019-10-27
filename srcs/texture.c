/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:30:54 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static SDL_Surface  *new_surface(int w, int h)
{
	Uint32			color[4];

	color[0] = 0x000000ff;
	color[1] = 0x0000ff00;
	color[2] = 0x00ff0000;
	color[3] = 0xff000000;
	return (SDL_CreateRGBSurface(0, w, h, 32,
        color[0], color[1], color[2], color[3]));
}

static void         create_surface(t_wolf *data)
{
    if (!(data->sprite[0].img = SDL_LoadBMP("img/doom.bmp")))
        clean_exit(data, "wolf3d: sdl loadbmp error: texture.c 1", 0);
    if (!(data->sprite[1].img = SDL_LoadBMP("img/brick.bmp")))
        clean_exit(data, "wolf3d: sdl loadbmp error: texture.c 2", 0);
    if (!(data->sprite[2].img = SDL_LoadBMP("img/rock.bmp")))
        clean_exit(data, "wolf3d: sdl loadbmp error: texture.c 3", 0);
    if (!(data->sprite[3].img = SDL_LoadBMP("img/stone.bmp")))
        clean_exit(data, "wolf3d: sdl loadbmp error: texture.c 4", 0);
    if (!(data->sprite[4].img = SDL_LoadBMP("img/wood.bmp")))
        clean_exit(data, "wolf3d: sdl loadbmp error: texture.c 5", 0);
    if (!(data->sprite[5].img = SDL_LoadBMP("img/grass.bmp")))
        clean_exit(data, "wolf3d: sdl loadbmp error: texture.c 6", 0);
    if (!(data->sprite[6].img = SDL_LoadBMP("img/night.bmp")))
        clean_exit(data, "wolf3d: sdl loadbmp error: texture.c 7", 0);
    if (!(data->sprite[7].img = SDL_LoadBMP("img/sand.bmp")))
        clean_exit(data, "wolf3d: sdl loadbmp error: texture.c 8", 0);
}

static void         create_texture(t_wolf *data)
{
    SDL_LockSurface(data->sprite[6].img);
    if (!(data->bgc = SDL_CreateTextureFromSurface(data->renderer, data->sprite[6].img)))
        clean_exit(data, "wolf3d: sdl creating texture fail: texture.c 1", 0);
    SDL_UnlockSurface(data->sprite[6].img);
    SDL_LockSurface(data->sprite[7].img);
    if (!(data->bgf = SDL_CreateTextureFromSurface(data->renderer, data->sprite[7].img)))
        clean_exit(data, "wolf3d: sdl creating texture fail: texture.c 2", 0);
    SDL_UnlockSurface(data->sprite[7].img);
}

void                load_surface_andtexture(t_wolf *data)
{
    create_surface(data);
    create_texture(data);
    if (!(data->screen = new_surface(W_WIDTH, W_HEIGHT)))
        clean_exit(data, "wolf3d: error creating RGB surface: texture.c", 0);
}
