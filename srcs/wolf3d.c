/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:30:54 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			get_padding(t_wolf *data)
{
	int		w;
	int		h;

	w = W_WIDTH / data->map.width;
	h = W_HEIGTH / data->map.height;
	data->map.padding = w > h ? h : w;
	if (data->map.padding < 7)
		data->map.padding = 7;
}

int				inblock(t_wolf *data, int x, int y)
{
	int	pos;

	pos = x + y * data->map.width;
	if (pos > data->map.len || pos < 0)
		return (-1);
	return (data->map.map[pos] == 1 ? 1 : 0);
}

void			get_list(t_wolf *data)
{
	int		i;
	t_bloc	*head;

	if (!(data->bloclist = (t_bloc *)ft_memalloc(sizeof(t_bloc))))
		clean_exit(data, "wolf3d: error malloc: bloclist 1", 0);
	head = data->bloclist;
	i = -1;
	while (++i < data->map.len)
	{
		data->bloclist->index = i;
		if (data->map.map[i] == 1)
		{
			data->bloclist->wall = 1;
		}
		else if (data->map.map[i] == 2)
		{
			data->bloclist->door = 1;
		}
		if (!(data->bloclist->next = (t_bloc *)ft_memalloc(sizeof(t_bloc))))
			clean_exit(data, "wolf3d: malloc error: bloclist 2", 0);
		data->bloclist = data->bloclist->next;
	}
	data->bloclist = head;
}

void			get_blocpos(t_wolf *data)
{
	t_bloc	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = data->bloclist;
	while (tmp->next)
	{
		if (i >= data->map.width)
		{
			i = 0;
			++j;
		}
		tmp->x = data->map.start + data->map.padding * i;
		tmp->y = data->map.padding * j;
		++i;
		tmp = tmp->next;
	}
	tmp = data->bloclist;
	while (tmp->index != data->player.pos)
		tmp = tmp->next;
	data->player.x = tmp->x + data->player.padding / 2;
	data->player.y = tmp->y + data->player.padding / 2;
}

void			wolf3d(t_wolf *data)
{
	int		i;

	data->map.start = 3 * W_WIDTH / 4;
	data->map.padding = (W_WIDTH - data->map.start) / 6 + 1;
	data->map.len = data->map.height * data->map.width;
	data->player.padding = data->map.padding / 2;
	i = -1;
	while (++i < data->map.len)
	{
		if (i > 0 && i % data->map.width == 0)
			ft_putchar('\n');
        if (i == data->player.pos)
            ft_putstr("\033[31mX\033[0m");
        else
		    ft_putnbr(data->map.map[i]);
	}
	ft_putchar('\n');
	get_list(data);
	get_blocpos(data);
	display_game(data);
}
