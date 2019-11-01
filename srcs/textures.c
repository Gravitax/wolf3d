/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
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

static void         load_objects(t_wolf *data)
{
    t_object    *head;
    int         i;

    if (!(data->object = (t_object *)ft_memalloc(sizeof(t_object))))
        clean_exit(data, "wolf3d: malloc error", 0);
    head = data->object;
    i = -1;
    while (++i < data->map.len)
    {
        if (data->map.map[i] == 3)
        {
            data->object->y = i / data->map.width;
            data->object->x = i - (data->object->y * data->map.width) + 1;
            data->object->type = data->map.map[i];
            data->object->si = 7;
            data->object->sprite = data->sprite[7];
            lst_pushback(data->object);
            if (data->object == NULL)
                clean_exit(data, "wolf3d: malloc error", 0);
            data->object = data->object->next;
        }
    }
    data->object = head;
}

static void         load_sprites(t_wolf *data)
{
    if (!(data->sprite[0].img = SDL_LoadBMP("img/doom.bmp")))
        clean_exit(data, "wolf3d: load_sprites error: texture.c 1", 0);
    if (!(data->sprite[1].img = SDL_LoadBMP("img/brick.bmp")))
        clean_exit(data, "wolf3d: load_sprites error: texture.c 2", 0);
    if (!(data->sprite[2].img = SDL_LoadBMP("img/rock.bmp")))
        clean_exit(data, "wolf3d: load_sprites error: texture.c 3", 0);
    if (!(data->sprite[3].img = SDL_LoadBMP("img/stone.bmp")))
        clean_exit(data, "wolf3d: load_sprites error: texture.c 4", 0);
    if (!(data->sprite[4].img = SDL_LoadBMP("img/wood.bmp")))
        clean_exit(data, "wolf3d: load_sprites error: texture.c 5", 0);
    if (!(data->sprite[5].img = SDL_LoadBMP("img/night.bmp")))
        clean_exit(data, "wolf3d: load_sprites error: texture.c 6", 0);
    if (!(data->sprite[6].img = SDL_LoadBMP("img/sand.bmp")))
        clean_exit(data, "wolf3d: load_sprites error: texture.c 7", 0);
    if (!(data->sprite[7].img = SDL_LoadBMP("img/monster.bmp")))
        clean_exit(data, "wolf3d: load_sprites error: texture.c 8", 0);
}

static void         create_textures(t_wolf *data)
{
    SDL_LockSurface(data->sprite[5].img);
    if (!(data->bgc = SDL_CreateTextureFromSurface(data->renderer,
    data->sprite[5].img)))
        clean_exit(data, "wolf3d: SDL_CreateTextures fail: texture.c 1", 0);
    SDL_UnlockSurface(data->sprite[5].img);
    SDL_LockSurface(data->sprite[6].img);
    if (!(data->bgf = SDL_CreateTextureFromSurface(data->renderer,
    data->sprite[6].img)))
        clean_exit(data, "wolf3d: SDL_CreateTextures fail: texture.c 2", 0);
    SDL_UnlockSurface(data->sprite[6].img);
}

void                load_surfaces_andtextures(t_wolf *data)
{
    load_sprites(data);
    load_objects(data);
    create_textures(data);
    if (!(data->screen = new_surface(W_WIDTH, W_HEIGHT)))
        clean_exit(data, "wolf3d: error creating RGB surface: texture.c", 0);
}
