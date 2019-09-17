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
    int         a;
    int         b;
    int         c;
    int         d;
    int         index;
    int         token;
    int         wall;
    int         door;
    t_bloc      *next;
};

typedef struct  s_player
{
    int         prev_pos;
    int         pos;
    double      x;
    double      y;
}               t_player;

typedef struct  s_map
{
    int         len;
    int         height;
    int         width;
    int         padding;
    int         *map;
}               t_map;


typedef struct  s_wolf
{
    int             sdl;
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
int				init_SDL(t_wolf *data);

int				inblock(t_wolf *data, int x, int y);

#endif
