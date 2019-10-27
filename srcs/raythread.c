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

// void			draw_pixel2(t_thread *data)
// {
// 	int			sx;
// 	int			sy;
// 	uint8_t		*p;

// 	SDL_LockSurface(data->img);
// 	sx = data->samplex * data->img->w;
// 	sy = data->sampley * data->img->h;
// 	p = (uint8_t *)data->img->pixels + sy * data->img->pitch
// 		+ sx * data->img->format->BytesPerPixel;
// 	SDL_UnlockSurface(data->img);
// 	SDL_SetRenderDrawColor(data->renderer, p[2], p[1], p[0], 100);
//     (void)p;
// }

// void            *draw_ray2(void *d)
// {
//     t_thread    *data;

//     data = (t_thread *)d;
//     while (data->y < data->y_max)
// 	{

// 		if (data->y <= data->floor && data->dst_towall < data->mdepth)
// 		{
// 			SDL_SetRenderDrawColor(data->renderer, 0, 0, 100, 100);
// 			data->sampley = ((float)data->y - (float)data->ceiling)
// 				/ ((float)data->floor - (float)data->ceiling);
// 			draw_pixel2(data);
// 		}
// 		else if (data->y > data->floor)
// 		{
// 			break ;
// 			float b = (((float)data->y - W_HEIGHT / 2) / ((float)W_HEIGHT / 2));
// 			SDL_SetRenderDrawColor(data->renderer, 200 * b, 200 * b, 200 * b, 100);
// 		}
// 		else
// 			continue ;
// 		SDL_RenderDrawPoint(data->renderer, data->x, data->y);
//         ++data->y;
// 	}
//     return (d);
// }

// void            raythread(t_wolf *data, int x)
// {
//     // t_thread    tab[NBTHREAD];
//     // pthread_t   t[NBTHREAD];

//     data->tdata = (t_thread *)ft_memalloc(sizeof(t_thread));

//     data->tdata->mdepth = data->map.depth;
//     data->tdata->x = x;
//     data->tdata->y = 0;
//     data->tdata->y_max = 0;
//     data->tdata->ceiling = data->raydata.ceiling;
//     data->tdata->dst_towall = data->raydata.dst_towall;
//     data->tdata->floor = data->raydata.floor;
//     data->tdata->samplex = data->raydata.samplex;
//     data->tdata->sampley = data->raydata.sampley;
//     data->tdata->img = data->surface[data->si].img;
//     data->tdata->renderer = data->renderer;
//     // int         i;

//     // i = -1;
//     // while (++i < NBTHREAD)
//     // {
//     //     printf("test%d\n", i);
//     //     ft_memcpy((void *)&tab[i], (void *)data->tdata, sizeof(t_thread));
//     //     tab[i].y = HTHREAD * i;
//     //     tab[i].y_max = HTHREAD * (i + 1);
//     //     printf("y: %d, ymax: %d\n", tab[i].y, tab[i].y_max);
//     //     pthread_create(&t[i], NULL, draw_ray2, &tab[i]);
//     // }
//     // while (i--)
//     //     pthread_join(t[i], NULL);

//     ft_memdel((void **)&data->tdata);
// }
