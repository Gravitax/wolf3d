/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datagame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/11/05 17:21:50 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void     get_list(t_wolf *data, t_object *list, int min, int max)
{
    t_object    *head;
    int         i;

    if (list == NULL)
        return ;
    head = list;
    i = -1;
    while (++i < data->map.len)
        if (data->map.map[i] >= min && data->map.map[i] <= max)
        {
            list->y = i / data->map.width;
            list->x = i - (list->y * data->map.width) + 1;
            list->type = data->map.map[i];
            list->si = list->type;
            list->sprite = data->sprite[list->si];
            list->delay = list->type * 10;
            list->hp = list->type * 20;
            list->speed = list->type;
            lst_pushback(list, (t_object *)ft_memalloc(sizeof(t_object)));
            if (list == NULL)
                clean_exit(data, "wolf3d: malloc error", 0);
            list = list->next;
        }
    list = head;
}

static void     background(t_wolf *data)
{
    SDL_LockSurface(data->sprite[0].img);
    if (!(data->bgc = SDL_CreateTextureFromSurface(data->renderer,
    data->sprite[0].img)))
        clean_exit(data, "wolf3d: SDL_CreateTextures fail", 0);
    SDL_UnlockSurface(data->sprite[0].img);
    SDL_LockSurface(data->sprite[1].img);
    if (!(data->bgf = SDL_CreateTextureFromSurface(data->renderer,
    data->sprite[1].img)))
        clean_exit(data, "wolf3d: SDL_CreateTextures fail", 0);
    SDL_UnlockSurface(data->sprite[1].img);
}

static void     weapons_data(t_wolf *data)
{
    data->player.wdata[0].damage = 40;
    data->player.wdata[0].hitbox = 1;
    data->player.wdata[0].range = 4;
    data->player.wdata[0].sfire = 1;
    data->player.wdata[0].si = 20;

    data->player.wdata[1].damage = 20;
    data->player.wdata[1].hitbox = 2;
    data->player.wdata[1].range = data->map.depth;
    data->player.wdata[1].sfire = 5;
    data->player.wdata[1].si = 22;

    data->player.wdata[2].damage = 100;
    data->player.wdata[2].hitbox = 10;
    data->player.wdata[2].range = data->map.depth;
    data->player.wdata[2].sfire = 1;
    data->player.wdata[2].si = 24;

    data->player.wdata[3].damage = 20;
    data->player.wdata[3].hitbox = 1;
    data->player.wdata[3].range = data->map.depth;
    data->player.wdata[3].sfire = 10;
    data->player.wdata[3].si = 26;
}

void            load_datagame(t_wolf *data)
{
    sprites(data);
    if (!(data->object = (t_object *)ft_memalloc(sizeof(t_object))))
        clean_exit(data, "wolf3d: malloc error", 0);
    if (!(data->monster = (t_object *)ft_memalloc(sizeof(t_object))))
        clean_exit(data, "wolf3d: malloc error", 0);
    get_list(data, data->object, 3, 5);
    get_list(data, data->monster, 6, 9);
    background(data);
    if (!(data->screen = new_surface(W_WIDTH, W_HEIGHT)))
        clean_exit(data, "wolf3d: error creating RGB surface", 0);
    get_nodes(data);
    weapons_data(data);
}
