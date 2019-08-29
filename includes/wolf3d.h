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

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../libft/libft.h"

typedef struct  s_player
{
    int         pos;
}               t_player;


typedef struct  s_wolf
{
    int         len;
    int         height;
    int         width;
    int         *map;
    char        *str;
    t_player    player;
}               t_wolf;

void            wolf3d(t_wolf *data);
void            free_thewolf(t_wolf *data, char *str, int token);

#endif
