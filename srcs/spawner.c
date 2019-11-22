/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/11/22 16:11:35 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static int		get_newmonsterhp(t_wolf *data, t_object *newmonster)
{
	int	hp;

	hp = 100000;
	if (newmonster->type == 7)
		hp = 100;
	if (newmonster->type == 8)
		hp = 200;
	if (newmonster->type == 9)
		hp = 400;
	return (hp + data->kill_score);
}

static void		create_newmonster(t_wolf *data)
{
	int			skin;
	t_object	*newmonster;

	newmonster = (t_object *)ft_memalloc(sizeof(t_object));
	newmonster->x = data->monster->x;
	newmonster->y = data->monster->y;
	skin = 7;
	if (data->kill_score > 10)
		skin = 8;
	if (data->kill_score > 20)
		skin = 9;
	newmonster->type = skin;
	newmonster->si = skin;
	newmonster->delay = newmonster->type * 10;
	newmonster->hp = get_newmonsterhp(data, newmonster);
	newmonster->hp_max = newmonster->hp;
	newmonster->sprite = data->sprite[newmonster->type];
	newmonster->speed = newmonster->type + data->kill_score / 10;
	if (newmonster->speed > 15)
		newmonster->speed = 15;
	lst_pushback(data->monster, newmonster);
	if (data->monster == NULL)
		clean_exit(data, "wolf3d: malloc error", 0);
}

void			spawner(t_wolf *data)
{
	int	monsters;

	monsters = lst_len(data->monster) - 1;
	if (monsters < 5)
		data->monster->delay = data->monster->type * 40;
	if (monsters < 10)
		data->monster->delay = data->monster->type * 80;
	else if (monsters < 20)
		data->monster->delay = data->monster->type * 160;
	else
	{
		data->monster->delay = data->monster->type * 320;
		return ;
	}
	create_newmonster(data);
}
