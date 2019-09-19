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

int             get_blocindex(t_wolf *data, int x, int y)
{
    int xc;
    int yc;

    xc = -1;
    while (x > 0)
    {
        x -= data->map.padding;
        ++xc;
    }
    yc = -1;
    while (y > 0)
    {
        y -= data->map.padding;
        ++yc;
    }
    return (xc + yc * data->map.width);
}

void            frame_delay(unsigned int frame)
{
    if (FRAME_DELAY > frame)
        SDL_Delay(FRAME_DELAY - frame);
    //printf("fps: %d\n", FRAME_DELAY - frame);
}

int				inbloc(t_wolf *data, int x, int y)
{
	int	pos;

	pos = x + y * data->map.width;
	if (pos > data->map.len || pos < 0)
		return (-1);
	return (data->map.map[pos] == 1 ? 1 : 0);
}
