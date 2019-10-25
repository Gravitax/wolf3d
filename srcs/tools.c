/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:05:22 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:08:19 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void     free_surface(t_wolf *data)
{
    int i;

    i = SNB;
    while (i--)
        if (data->surface[i].img)
            SDL_FreeSurface(data->surface[i].img);
}

void            clean_exit(t_wolf *data, char *str, int token)
{
    if (data)
    {
        if (data->str)
            ft_strdel(&data->str);
        if (data->map.map)
            free(data->map.map);
        if (data->sdl_on)
        {
            if (data->pWindow)
                SDL_DestroyWindow(data->pWindow);
            if (data->renderer)
                SDL_DestroyRenderer(data->renderer);
            free_surface(data);
            SDL_Quit();
        }
    }
    if (str)
       ft_putendl_fd(str, 2);
    exit(token ? EXIT_SUCCESS : EXIT_FAILURE);
}

int         frame_delay(int frame)
{
    if (FRAME_DELAY > frame)
        SDL_Delay(frame - FRAME_DELAY);
    return (frame - FRAME_DELAY);
}
