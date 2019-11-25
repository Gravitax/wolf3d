/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:48:08 by maboye            #+#    #+#             */
/*   Updated: 2019/11/25 21:42:33 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			game_over(t_wolf *data)
{
	if (data)
	{
		/*if (data->sdl_on)
		{
			if (data->pwindow)
				SDL_DestroyWindow(data->pwindow);
			if (data->renderer)
				SDL_DestroyRenderer(data->renderer);
			SDL_Quit();
		}*/
		//ft_strdel(&data->str);
		//ft_memdel((void **)&data->map.map);
		printf("end");
		lst_free(data->object);
		free_surfaces(data);
		lst_free(data->monster);
		alst_free(data->pfdata.alst);
		ft_memdel((void **)&data->pfdata.list);
	}
	w_pause(data);
	printf("restart");
}