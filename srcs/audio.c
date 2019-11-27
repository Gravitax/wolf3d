/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 22:09:50 by saneveu           #+#    #+#             */
/*   Updated: 2019/11/26 23:54:38 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"


void            audio_init(t_wolf *data)
{
    data->sound.walk = Mix_LoadWAV("../sound/chunk/walk1.wav");
    //data->sound.music = Mix_LoadMUS("../sound/music/music.wav"); //trouver une musique
    if (data->sound.walk == NULL)
        clean_exit(data, "wold3d: Mix_LoadWAV fail", 0);
}

void            free_sound(t_wolf *data)
{
    Mix_FreeMusic(data->sound.music);
    Mix_FreeChunk(data->sound.walk);
    Mix_FreeChunk(data->sound.fire);
   //Mix_FreeChunk(data->sound.);
   //Mix_FreeChunk(data->sound.walk);
}

void            play_sound(t_wolf *data, Mix_Chunk *chunk)
{
    if (Mix_PlayChannel(-1, chunk, 0) == - 1)
        clean_exit(data, "Wolf3d: Play sound fail", 0);
}