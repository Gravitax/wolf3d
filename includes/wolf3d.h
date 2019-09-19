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
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>

# include "../libft/libft.h"

# define    FPS         60
# define    FRAME_DELAY 1000 / FPS
# define    W_WIDTH     800
# define    W_HEIGTH    600

typedef struct  s_bloc  t_bloc;

struct          s_bloc
{
    int         x;
    int         y;
    int         mid;
    int         index;
    int         wall;
    int         door;
    t_bloc      *next;
};

typedef struct  s_player
{
    int         x;
    int         y;
    int         speed;
    int         pos;
    int         padding;
}               t_player;

typedef struct  s_map
{
    int         start;
    int         limit;
    int         diff;
    int         len;
    int         height;
    int         width;
    int         padding;
    int         *map;
}               t_map;


typedef struct  s_wolf
{
    int             sdl_token;
    char            *str;
    int             x;
    int             y;
    unsigned int   frame_start;
    t_map           map;
    t_player        player;
    t_bloc          *bloclist;
    SDL_Event       event;
    SDL_Window	    *pWindow;
    SDL_Renderer    *renderer;
}               t_wolf;

void            clean_exit(t_wolf *data, char *str, int token);
void            wolf3d(t_wolf *data);
void            draw_map(t_wolf *data);

void    		launch_game(t_wolf *data);
void            sdl_event(t_wolf *data);

void            key_event(t_wolf *data);
void            mouse_event(t_wolf *data);

int				inbloc(t_wolf *data, int x, int y);
int             get_blocindex(t_wolf *data, int x, int y);

void            frame_delay(unsigned int frame);

#endif
