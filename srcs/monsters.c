/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monsters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/12/02 17:38:40 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			remove_objects(t_wolf *data, t_object *list)
{
	t_object	*tmp;
	t_object	*head;

	head = list;
	while (list && list->dead == 1)
	{
		tmp = list->next;
		ft_memdel((void **)&list);
		list = tmp;
		head = list;
	}
	while (list)
	{
		tmp = list;
		list = list->next;
		while (list && list->dead == 1)
		{
			tmp->next = list->next;
			ft_memdel((void **)&list);
			list = tmp->next;
		}
	}
	list = head;
}

static void		smoothness(t_wolf *data, t_node *current)
{
	int		pos;
	float	tmpx;
	float	tmpy;

	if (data->monster->data.dst_fromplayer > data->map.depth)
		return ;
	tmpx = (current->x + 0.5f - data->monster->x) * data->monster->speed;
	tmpy = (current->y + 0.5f - data->monster->y) * data->monster->speed;
	data->monster->x += tmpx;
	data->monster->y += tmpy;
	pos = (int)data->monster->x
		+ data->map.width * (int)data->monster->y;
	if (data->monster->x < 0
		|| data->monster->x > data->map.width
		|| data->monster->y < 0
		|| data->monster->y > data->map.height
		|| data->map.map[pos] == 1)
	{
		data->monster->x -= tmpx;
		data->monster->y -= tmpy;
	}
}

static void		monster_moves(t_wolf *data)
{
	t_node	*current;

	astar(data);
	current = data->pfdata.end;
	if (current == NULL)
		return ;
	while (current->parent)
	{
		if (current->parent == data->pfdata.start)
			break ;
		current = current->parent;
	}
	smoothness(data, current);
	data->monster->delay = data->monster->type + 10;
}

static void		monster_actions(t_wolf *data)
{
	float	dst;

	if (data->monster->dead == 1)
		return ;
	data->pfdata.start = &data->pfdata.list[data->monster->i];
	data->pfdata.end = &data->pfdata.list[data->player.pos];
	dst = distance(data->monster->x, data->monster->y,
			data->pfdata.end->x, data->pfdata.end->y);
	if (dst > 2.5f)
	{
		data->monster->si = data->monster->type;
		if (dst < 12.5f || data->monster->hp < data->monster->hp_max)
			monster_moves(data);
	}
	else
	{
		data->monster->si = data->monster->type + 3;
		data->player.health -= data->monster->type * 2;
		data->monster->delay = data->monster->type * 10;
		if (data->player.health < 1)
			game_over(data);
	}
}

void			monsters(t_wolf *data)
{
	t_object	*head;

	head = data->monster;
	while (data->monster)
	{
		if (data->monster->type > 5 && data->monster->type < 10)
			if (--data->monster->delay < 1)
			{
				if (data->monster->type == 6)
					spawner(data);
				else
					monster_actions(data);
			}
		data->monster = data->monster->next;
	}
	data->monster = head;
	objects(data, data->monster);
}
