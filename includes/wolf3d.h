/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:48:08 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:10:56 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>

# include <SDL2/SDL.h>

# include "../libft/libft.h"

# define    W_WIDTH     800
# define    W_HEIGTH    600
# define    SNB         8

# define    FPS         20

# define    NBTHREAD    8
# define    WTHREAD     W_WIDTH / NBTHREAD

# define    KA          0
# define    KE          1
# define    KZ          2
# define    KQ          3
# define    KS          4
# define    KD          5
# define    KNB         6

typedef struct  s_surface
{
    SDL_Surface *img;
}               t_surface;

typedef struct  s_player
{
    int         pos;
    float       angle;
    float       fov;
    float       speed;
    float       x;
    float       y;
}               t_player;

typedef struct  s_raydata
{
    int         ceiling;
    int         floor;
    int         x;
    int         x_max;
    float       angle;
    float       bmx;
    float       bmy;
    float       dst_towall;
    float       eyex;
    float       eyey;
    float       ray_step;
    float       samplex;
    float       sampley;
    float       testangle;
    float       testx;
    float       testy;
}               t_raydata;

typedef struct  s_map
{
    int         len;
    int         height;
    int         width;
    int         *map;
    float       depth;
}               t_map;

typedef struct  s_wolf
{
    int             fps;
    int             sdl_on;
    int             si;
    int             key[KNB];
    char            *str;
    float           etime;
    float           frame_start;
    t_map           map;
    t_player        player;
    t_raydata       raydata;
    t_surface       surface[SNB];
    SDL_Event       event;
    SDL_Window	    *pWindow;
    SDL_Renderer    *renderer;
}               t_wolf;

void			get_blockside(t_wolf *data, int testx, int testy);
void            minimap(t_wolf *data);
void    		*raycasting(void *d);
void            raythread(t_wolf *data);
void            wolf3d(t_wolf *data);

void            clean_exit(t_wolf *data, char *str, int token);

void            mouse_event(t_wolf *data);
void            sdl_event(t_wolf *data);

#endif
