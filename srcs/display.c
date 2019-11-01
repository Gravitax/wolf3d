/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:30:54 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void     display_textures(t_wolf *data)
{
    unsigned int    *pixels;
    SDL_Rect        rect;
    int             i;

    rect.w = W_WIDTH;
    rect.h = W_HEIGHT / 2;
    rect.x = 0;
    rect.y = W_HEIGHT / 2;
    SDL_RenderCopy(data->renderer, data->bgf, NULL, &rect);
    rect.y = 0;
    SDL_RenderCopy(data->renderer, data->bgc, NULL, &rect);
    rect.h = W_HEIGHT;
    SDL_LockSurface(data->screen);
    data->window = SDL_CreateTextureFromSurface(data->renderer, data->screen);
    SDL_RenderCopy(data->renderer, data->window, NULL, &rect);
    pixels = (unsigned int *)data->screen->pixels;
    i = -1;
    while (++i < W_WIDTH * W_HEIGHT)
        pixels[i] = 0x000000;
    SDL_UnlockSurface(data->screen);
}

void            display(t_wolf *data)
{
    //raythread(data);
    raycasting(data);
    objects(data);
    display_textures(data);
    if (data->key[KM])
        minimap(data);
}
