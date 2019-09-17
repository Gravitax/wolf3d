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
	if (pos > data->map.len)
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
		if (data->map.map[i] == 1)
		{
			data->bloclist->token = 1;
			data->bloclist->wall = 1;
		}
		else if (data->map.map[i] == 2)
		{
			data->bloclist->token = 1;
			data->bloclist->door = 1;
		}
		data->bloclist->index = i;
		if (!(data->bloclist->next = (t_bloc *)ft_memalloc(sizeof(t_bloc))))
			clean_exit(data, "wolf3d: malloc error: bloclist 2", 0);
		data->bloclist = data->bloclist->next;
	}
	data->bloclist = head;
}

void			wolf3d(t_wolf *data)
{
	int		i;

	data->map.len = data->map.height * data->map.width;
	get_padding(data);
    printf("player block: (%d)\n\n", (data->player.pos + 1));
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
	printf("ww: (%d), wh: (%d)\n", W_WIDTH, W_HEIGTH);
	printf("\npadding: (%d)\n", data->map.padding);
	printf("len: (%d)\n", data->map.len);
	printf("w: (%d), h: (%d)\n", data->map.width, data->map.height);
	get_list(data);
	init_SDL(data);
}
