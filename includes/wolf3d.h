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

typedef struct  s_player
{
    int         prev_pos;
    int         pos;
    double      x;
    double      y;
}               t_player;

typedef struct  s_ray
{
    int         len;
}               t_ray;

typedef struct  s_vector
{
    double      x;
    double      y;
}               t_vector;

typedef struct  s_wolf
{
    int             len;
    int             height;
    int             width;
    int             *map;
    int             padding;
    char            *str;
    t_player        player;
    SDL_Window	    *pWindow;
    SDL_Renderer    *renderer;
    SDL_Event       event;
}               t_wolf;

void            wolf3d(t_wolf *data);
void            free_thewolf(t_wolf *data, char *str, int token);
int				init_SDL(t_wolf *data);

#endif
