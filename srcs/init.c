/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:30:54 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/wolf3d.h"

void            draw_map(t_wolf *data)
{
    int i;
    int j;
    int spc = 0;

    i = 0;
    j = 0;
    SDL_SetRenderDrawColor(data->renderer, 255, 0, 0, 255);
    while (i * j < data->len + 1)
    {
    	if (i >= data->width + 1) {
			++j;
            i = 0;
        }
        if (i + j * data->width == data->player.prev_pos)
        {
            SDL_SetRenderDrawColor(data->renderer, 0, 0, 0, 0);
            SDL_Rect pos = {data->padding * i + spc,  data->padding * j,
                data->padding, data->padding};
            SDL_RenderFillRect(data->renderer, &pos);
            SDL_SetRenderDrawColor(data->renderer, 255, 0, 0, 255);
        }
        if (j > 0)
        {
            SDL_RenderDrawLine(data->renderer,
                data->padding * i + spc, data->padding * (j - 1),
                data->padding * i + spc, data->padding * j);
        }
        if (i < data->width)
        {
            SDL_RenderDrawLine(data->renderer,
                data->padding * i + spc, data->padding * j,
                data->padding * (i + 1) + spc, data->padding * j);
        }
        if (i + j * data->width == data->player.pos)
        {
            //printf("player pos: (%d)\n", i + j * data->height);
            SDL_Rect pos = {data->padding * i + spc,  data->padding * j,
                data->padding, data->padding};
            SDL_RenderFillRect(data->renderer, &pos);
        }
        ++i;
    }
    SDL_RenderPresent(data->renderer);
    return ;
}

void            handle_event(t_wolf *data)
{
    data->player.prev_pos = data->player.pos;
    if (data->event.key.keysym.sym == SDLK_UP)
    {
        if (data->player.pos - data->width < 0)
            return ;
        data->player.pos -= data->width;
    }
    if (data->event.key.keysym.sym == SDLK_DOWN)
    {
        if (data->player.pos + data->width > data->len - 1)
            return ;
        data->player.pos += data->width;
    }
    if (data->event.key.keysym.sym == SDLK_LEFT)
    {
        if (data->player.pos % data->width == 0)
            return ;
        data->player.pos--;
    }
    if (data->event.key.keysym.sym == SDLK_RIGHT)
    {
        if ((data->player.pos + 1) % data->width == 0)
            return ;
        data->player.pos++;
    }
}

int             init_SDL(t_wolf *data)
{
    /* Initialisation */
    if (SDL_Init(SDL_INIT_VIDEO) == -1) 
    { 
        fprintf(stderr, "Erreur d'initialisation de la SDL: %s\n", SDL_GetError());
        exit (EXIT_FAILURE);
    }


    data->pWindow = SDL_CreateWindow("maboye wolf3d",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		W_WIDTH, W_HEIGTH, 0);
    if (data->pWindow) 
    { 
        data->renderer = SDL_CreateRenderer(data->pWindow, -1, 0);
		while (1)
		{
			if (SDL_PollEvent(&data->event))
            {
                if (data->event.type == SDL_QUIT)
                    break ;
                if (data->event.type == SDL_KEYUP)
                {
                    if (data->event.key.keysym.sym == SDLK_ESCAPE)
                        break ;
                    else
                        handle_event(data);
                }
            }
            draw_map(data);
		}
        SDL_DestroyRenderer(data->renderer);
		SDL_DestroyWindow(data->pWindow);
    } 
    else
        fprintf(stderr, "Erreur de creation de la fenetre: %s\n", SDL_GetError());
    SDL_Quit();
    return (EXIT_SUCCESS);
}
