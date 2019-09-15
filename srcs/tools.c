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

void        free_thewolf(t_wolf *data, char *str, int token)
{
    if (data)
    {
        if (data->str)
            ft_strdel(&data->str);
        if (data->map)
            free((void *)data->map);
    }
    if (token)
    {
        if (str)
            write(2, &str, ft_strlen(str));
        exit(0);
    }
}
