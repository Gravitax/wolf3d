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

# define    BLOCK_SIZE  10
# define    W_WIDTH     800
# define    W_HEIGTH    600

typedef struct  s_bloc  t_bloc;

struct          s_bloc
{
    int         x;
    int         y;
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
    t_map           map;
    t_player        player;
    t_bloc          *bloclist;
    SDL_Event       event;
    SDL_Window	    *pWindow;
    SDL_Renderer    *renderer;
}               t_wolf;

void            clean_exit(t_wolf *data, char *str, int token);
void            wolf3d(t_wolf *data);

void    		display_game(t_wolf *data);
void            handle_sdl_event(t_wolf *data);

void            keydown_event(t_wolf *data);
void            keyup_event(t_wolf *data);
void            mouse_event(t_wolf *data);

int				inblock(t_wolf *data, int x, int y);

#endif
