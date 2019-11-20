/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raythread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:30:54 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void            raythread(t_wolf *data)
{
    t_wolf      tab[NBTHREAD];
    pthread_t   t[NBTHREAD];  
    int         i;

    i = -1;
    while (++i < NBTHREAD)
    {
        ft_memcpy((void *)&tab[i], (void *)data, sizeof(t_wolf));
        tab[i].i = WTHREAD * i;
        tab[i].i_max = WTHREAD * (i + 1);
        pthread_create(&t[i], NULL, raycasting, &tab[i]);
    }
    while (i--)
        pthread_join(t[i], NULL);
}
