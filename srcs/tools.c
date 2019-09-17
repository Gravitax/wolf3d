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

static void     lst_del(t_bloc *list)
{
    if (list)
    {
        lst_del(list->next);
        free(list);
        list = NULL;
    }
}

void            clean_exit(t_wolf *data, char *str, int token)
{

    if (data)
    {
        if (data->str)
            ft_strdel(&data->str);
        if (data->map.map)
            free(data->map.map);
        if (data->bloclist)
            lst_del(data->bloclist);
        if (data->pWindow)
            SDL_DestroyWindow(data->pWindow);
        if (data->renderer)
            SDL_DestroyRenderer(data->renderer);
        if (data->sdl_token)
            SDL_Quit();
    }
    if (str)
       ft_putendl_fd(str, 2);
    exit(token ? EXIT_SUCCESS : EXIT_FAILURE);
}
