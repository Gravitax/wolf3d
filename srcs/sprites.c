/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:30:54 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void     sprites_monsters(t_wolf *data)
{
    if (!(data->sprite[6].img = SDL_LoadBMP("img/golem.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[7].img = SDL_LoadBMP("img/monsters/monster.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[8].img = SDL_LoadBMP("img/monsters/monster2.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[9].img = SDL_LoadBMP("img/monsters/monster3.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[14].img = SDL_LoadBMP("img/monsters/monster2atk.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[15].img = SDL_LoadBMP("img/monsters/monster2l.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[16].img = SDL_LoadBMP("img/monsters/monster2r.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
}

static void     sprites_objects(t_wolf *data)
{
    if (!(data->sprite[3].img = SDL_LoadBMP("img/doom.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[4].img = SDL_LoadBMP("img/doom.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[5].img = SDL_LoadBMP("img/doom.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
}

static void     sprites_weapons(t_wolf *data)
{
    if (!(data->sprite[17].img = SDL_LoadBMP("img/weapons/gun1.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[18].img = SDL_LoadBMP("img/weapons/gun2.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[19].img = SDL_LoadBMP("img/weapons/shotgun1.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[20].img = SDL_LoadBMP("img/weapons/shotgun2.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[21].img = SDL_LoadBMP("img/weapons/shotgun1.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[22].img = SDL_LoadBMP("img/weapons/shotgun2.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
}

void            sprites(t_wolf *data)
{
    if (!(data->sprite[10].img = SDL_LoadBMP("img/textures/brick.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[11].img = SDL_LoadBMP("img/textures/rock.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[12].img = SDL_LoadBMP("img/textures/stone.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[13].img = SDL_LoadBMP("img/textures/wood.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[0].img = SDL_LoadBMP("img/textures/night.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[1].img = SDL_LoadBMP("img/textures/sand.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[2].img = SDL_LoadBMP("img/doom.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    sprites_monsters(data);
    sprites_objects(data);
    sprites_weapons(data);
}
