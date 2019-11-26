/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:05:22 by maboye            #+#    #+#             */
/*   Updated: 2019/11/26 16:19:55 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			lst_free(t_object *list)
{
	t_object	*tmp;

	while (list)
	{
		tmp = list->next;
		ft_memdel((void **)&list);
		if (tmp)
			list = tmp;
	}
}

int				lst_len(t_object *list)
{
	int			i;
	t_object	*tmp;

	if (list == NULL)
		return (0);
	tmp = list;
	i = 0;
	while (tmp)
	{
		++i;
		tmp = tmp->next;
	}
	return (i);
}

void			lst_pushback(t_object *list, t_object *node)
{
	t_object	*head;

	head = list;
	if (node == NULL)
		lst_free(head);
	if (list)
	{
		while (list->next)
			list = list->next;
		if (!(list->next = node))
		{
			lst_free(head);
			return ;
		}
		list = head;
	}
}

void		free_surfaces(t_wolf *data)
{
	int	i;

	i = SNB;
	while (i--)
		if (data->sprite[i].img)
			SDL_FreeSurface(data->sprite[i].img);
	if (data->screen)
		SDL_FreeSurface(data->screen);
}

void			clean_exit(t_wolf *data, char *str, int token)
{
	if (data)
	{
		if (data->sdl_on)
		{
			if (data->pwindow)
				SDL_DestroyWindow(data->pwindow);
			if (data->renderer)
				SDL_DestroyRenderer(data->renderer);
			free_surfaces(data);
			TTF_Quit();
			SDL_Quit();
		}
		ft_strdel(&data->str);
		ft_memdel((void **)&data->map.map);
		lst_free(data->object);
		lst_free(data->monster);
		ft_memdel((void **)&data->pfdata.list);
		data = NULL;
	}
	if (str)
		ft_putendl_fd(str, 2);
	exit(token ? EXIT_SUCCESS : EXIT_FAILURE);
}
