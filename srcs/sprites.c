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

static void     sprites_ammo(t_wolf *data)
{
    if (!(data->sprite[17].img = SDL_LoadBMP("img/fireball.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
}

static void     sprites_monsters(t_wolf *data)
{
    if (!(data->sprite[7].img = SDL_LoadBMP("img/monster.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[8].img = SDL_LoadBMP("img/monster2.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[9].img = SDL_LoadBMP("img/monster3.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[14].img = SDL_LoadBMP("img/monster2atk.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[15].img = SDL_LoadBMP("img/monster2left.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[16].img = SDL_LoadBMP("img/monster2right.bmp")))
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
    if (!(data->sprite[6].img = SDL_LoadBMP("img/doom.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
}

static void     sprites_weapons(t_wolf *data)
{
    (void)data;
    return ;
}

void            sprites(t_wolf *data)
{
    if (!(data->sprite[10].img = SDL_LoadBMP("img/brick.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[11].img = SDL_LoadBMP("img/rock.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[12].img = SDL_LoadBMP("img/stone.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[13].img = SDL_LoadBMP("img/wood.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[0].img = SDL_LoadBMP("img/night.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[1].img = SDL_LoadBMP("img/sand.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    if (!(data->sprite[2].img = SDL_LoadBMP("img/monster.bmp")))
        clean_exit(data, "wolf3d: load_sprites error", 0);
    sprites_ammo(data);
    sprites_monsters(data);
    sprites_objects(data);
    sprites_weapons(data);
}
