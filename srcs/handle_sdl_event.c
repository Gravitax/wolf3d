/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sdl_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:30:54 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void        handle_sdl_event(t_wolf *data)
{
    if (SDL_PollEvent(&data->event))
    {
        if (data->event.type == SDL_QUIT)
            clean_exit(data, NULL, 1);
        if (data->event.type == SDL_KEYUP)
        {
            if (data->event.key.keysym.sym == SDLK_ESCAPE)
                clean_exit(data, NULL, 1);
            else
                keyup_event(data);
        }
        else if (data->event.type == SDL_KEYDOWN)
            keydown_event(data);
    }
}
