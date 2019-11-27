/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 22:09:50 by saneveu           #+#    #+#             */
/*   Updated: 2019/11/27 20:32:39 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"


void            audio_init(t_wolf *data)
{
    data->sound.token = 1;
    Mix_AllocateChannels(16);
    data->sound.walk = Mix_LoadWAV("sound/chunk/walk2.wav");
    data->sound.hand = Mix_LoadWAV("sound/chunk/PUNCH.wav");
    data->sound.gun = Mix_LoadWAV("sound/chunk/shoot2.wav");
    data->sound.fusil = Mix_LoadWAV("sound/chunk/shoot.wav");
    data->sound.shotgun = Mix_LoadWAV("sound/chunk/shotgun.wav");
    data->sound.NMIhit = Mix_LoadWAV("sound/chunk/HITmonster.wav");
    data->sound.NMIdeath = Mix_LoadWAV("sound/chunk/DEATHmonster.wav");
    data->sound.NMIspawn = Mix_LoadWAV("sound/chunk/SpawnMonster.wav");
    data->sound.NMIatk = Mix_LoadWAV("sound/chunk/ATTACKmonster2.wav");
    data->sound.PlayerHit = Mix_LoadWAV("sound/chunk/PLAYERhit.wav");
    data->sound.PlayerDeath = Mix_LoadWAV("sound/chunk/PLAYERdeath.wav");
    data->sound.PlayerSpawn = Mix_LoadWAV("sound/chunk/PLAYERspawn.wav");
    data->sound.switchgun = Mix_LoadWAV("sound/chunk/SWITCHgun.wav");
    data->sound.tic = Mix_LoadWAV("sound/chunk/tic.wav");
    data->sound.InGmMusic = Mix_LoadMUS("sound/music/SignOfEvil.wav");
    data->sound.PauseMusic = Mix_LoadMUS("sound/music/AtDoomsGate.wav");
    if (data->sound.walk == NULL)
        clean_exit(data, "wold3d: Mix_LoadWAV fail", 0);
}

void            free_sound(t_wolf *data)
{
    Mix_HaltChannel(-1);
    Mix_FreeMusic(data->sound.InGmMusic);
    Mix_FreeMusic(data->sound.PauseMusic);
    Mix_FreeChunk(data->sound.walk);
    Mix_FreeChunk(data->sound.hand);
    Mix_FreeChunk(data->sound.gun);
    Mix_FreeChunk(data->sound.fusil);
    Mix_FreeChunk(data->sound.shotgun);
    Mix_FreeChunk(data->sound.NMIhit); 
    Mix_FreeChunk(data->sound.NMIdeath);
    Mix_FreeChunk(data->sound.NMIspawn);
    Mix_FreeChunk(data->sound.NMIatk);
    Mix_FreeChunk(data->sound.PlayerHit);
    Mix_FreeChunk(data->sound.PlayerDeath);
    Mix_FreeChunk(data->sound.PlayerSpawn);
    Mix_FreeChunk(data->sound.switchgun);
    Mix_FreeChunk(data->sound.tic);
    Mix_AllocateChannels(0);
    data->sound.token = 0;
}

void            play_sound(t_wolf *data, Mix_Chunk *chunk, int channel)
{
    if (Mix_PlayChannelTimed(channel, chunk, 0, 500) == - 1)
        clean_exit(data, "Wolf3d: Play sound fail", 0);
}

void            play_music(t_wolf *data, Mix_Music *music)
{
    if (Mix_PlayingMusic() == 0)
    {
        if (Mix_PlayMusic(music, -1))
            clean_exit(data, "wolf3d: Mix_PlayMusic fail", 0);
    }
    else
    {
        Mix_HaltMusic();
        if (music == NULL)
            return ;
        else if (Mix_PlayMusic(music, -1))
            clean_exit(data, "wolf3d: Mix_PlayMusic fail", 0);
    }
}