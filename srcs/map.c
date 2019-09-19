/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:48:08 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:10:56 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void     draw_rect(t_wolf *data, int i, int j, int padding)
{
    SDL_Rect rect;

    rect.x = i;
    rect.y = j;
    rect.h = padding;
    rect.w = padding;
    SDL_RenderFillRect(data->renderer, &rect);
}

static void     center_map(t_wolf *data)
{
    t_bloc  *tmp;

    if (data->map.len < 26)
        return ;
    tmp = data->bloclist;
    while (tmp->next)
    {
        if (tmp->index == data->player.pos)
        {
            data->x = (W_WIDTH / 8 + data->map.start) - tmp->x;
            data->y =  (W_HEIGTH / 8) - tmp->y;
            tmp = data->bloclist;
            while (tmp->next)
            {
                tmp->x += data->x;
                tmp->y += data->y;
                tmp = tmp->next;
            }
            data->player.x += data->x;
            data->player.y += data->y;
            return ;
        }
        tmp = tmp->next;
    }
}

static void     reset_map(t_wolf *data)
{
    t_bloc  *tmp;

    if (data->map.len < 26)
        return ;
    tmp = data->bloclist;
    while (tmp->next)
    {
        tmp->x -= data->x;
        tmp->y -= data->y;
        tmp = tmp->next;
    }
    data->player.x -= data->x;
    data->player.y -= data->y;
}

static void     draw_border(t_wolf *data)
{
    SDL_Rect rect;

    rect.x = data->map.start;
    rect.y = 0;
    rect.h = W_HEIGTH / 3;
    rect.w = W_WIDTH / 3;
    SDL_SetRenderDrawColor(data->renderer, 100, 100, 100, 100);
    SDL_RenderFillRect(data->renderer, &rect);
}

void            draw_map(t_wolf *data)
{
    t_bloc  *tmp;

    SDL_RenderClear(data->renderer);
    center_map(data);
    draw_border(data);
    tmp = data->bloclist;
    while (tmp->next)
    {     
        if (tmp->wall)
            SDL_SetRenderDrawColor(data->renderer, 0, 0, 255, 100);
        else if (tmp->door)
            SDL_SetRenderDrawColor(data->renderer, 255, 0, 255, 100);
        else
            SDL_SetRenderDrawColor(data->renderer, 255, 255, 255, 100);
        if (tmp->y <= data->map.limit && tmp->x <= W_WIDTH
                && tmp->y >= 0 && tmp->x >= data->map.start)
            draw_rect(data, tmp->x, tmp->y, data->map.padding);
        tmp = tmp->next;
    }
    SDL_SetRenderDrawColor(data->renderer, 0, 0, 0, 100);
    draw_rect(data, data->player.x, data->player.y, data->player.padding);
    SDL_RenderPresent(data->renderer);
    reset_map(data);
}
