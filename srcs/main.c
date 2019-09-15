/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:47:19 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:37:02 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static int      stock_map(t_wolf *data, char c, int i)
{
    if (c >= '0' && c <= '9')
	    data->map[i] = c - '0';
    else if (c == 'X' && data->player.pos == -1)
        data->player.pos = i;
    else
        return (0);
    return (1);
}

static int		parse_map(t_wolf *data)
{
	int		i;
	char	*tmp;

	if (data->map == NULL || data->str == NULL || data->len < 1)
		return (0);
    data->player.pos = -1;
	i = 0;
	tmp = data->str;
	while (tmp && tmp[i])
	{
        while (stock_map(data, tmp[i], i) == 1)
            ++i;
		if (tmp[i] == '\n')
		{
			data->width = data->width < 1 ? i : data->width;
			++tmp;
			++data->height;
		}
		else
			break ;
	}
	if (data->player.pos == -1)
		return (0);
	data->width = data->width < 1 ? 1 : data->width;
	return (i % data->width == tmp[i] ? 1 : 0);
}

static int		get_map(t_wolf *data, int file)
{
	int		r;
	char	buff[BUFF_SIZE];

	if (file == -1)
	{
		close(file);
		return (0);
	}
	data->str = (char *)ft_memalloc(1);
	while (data->str && (r = read(file, buff, BUFF_SIZE)))
	{
		if (r == -1)
		{
			close(file);
			return (0);
		}
		buff[r] = '\0';
		data->str = ft_strfjoin(data->str, buff, 1);
	}
	close(file);
	data->len = (int)ft_strlen(data->str) + 1;
	data->map = (int *)ft_memalloc(sizeof(int)
		* (data->len - (int)ft_sqrt(data->len)));
	return (parse_map(data));
}

int				main(int ac, char **av)
{
	t_wolf	data;

	if (ac == 2)
	{
		ft_memset(&data, 0, sizeof(t_wolf));
		if (get_map(&data, open(av[1], O_RDONLY)) == 1)
			wolf3d(&data);
		else
			write(2, "wolf3d: map error\n", 18);
		ft_strdel(&data.str);
		free_thewolf(&data, NULL, 0);
	}
	else
		write(2, "wolf3d: usage: ./wolf3d [ valid_map ]\n", 38);
	return (-ac);
}
