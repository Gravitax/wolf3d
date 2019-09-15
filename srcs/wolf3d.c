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

	w = W_WIDTH / data->width;
	h = W_HEIGTH / data->height;
	data->padding = w > h ? h : w;
	--data->padding;
}

int				inblock(t_wolf *data, int x, int y)
{
	int	pos;

	pos = x + y * data->height;
	if (pos > data->len)
		return (-1);
	return (data->map[pos] == 1 ? 1 : 0);
}

void			wolf3d(t_wolf *data)
{
	int		i;

	data->len = data->height * data->width;
	get_padding(data);
    printf("player block: (%d)\n\n", (data->player.pos + 1));
	i = -1;
	while (++i < data->len)
	{
		if (i > 0 && i % data->width == 0)
			ft_putchar('\n');
        if (i == data->player.pos)
            ft_putstr("\033[31mX\033[0m");
        else
		    ft_putnbr(data->map[i]);
	}
	ft_putchar('\n');
	printf("ww: (%d), wh: (%d)\n", W_WIDTH, W_HEIGTH);
	printf("\npadding: (%d)\n", data->padding);
	printf("len: (%d)\n", data->len);
	printf("w: (%d), h: (%d)\n", data->width, data->height);
	init_SDL(data);
	printf("(%d)\n", inblock(data, 0, 0));
}
