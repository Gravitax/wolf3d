/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grenada.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/12/02 17:40:25 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		explosions(t_wolf *data, t_object *list)
{
	t_object	*head;
	float		damage;
	float		dst;

	head = data->monster;
	while (data->monster)
	{
		dst = distance(list->x, list->y,
				data->monster->x, data->monster->y);
		damage = 300 * (1 / dst);
		if (dst < 2.5f)
		{
			deal_damage_tomonster(data, data->monster, damage);
			list->si = 25;
		}
		data->monster = data->monster->next;
	}
}

void			object_actions(t_wolf *data, t_object *list)
{
	t_object	*head;

	if (list == NULL || list->type > 5 || list->type < 3)
		return ;
	list->x += list->vx * list->speed;
	list->y += list->vy * list->speed;
	if (data->map.map[(int)list->x + data->map.width * (int)list->y] == 1)
		list->dead = 1;
	list->i = (int)list->x + data->map.width * (int)list->y;
	head = data->monster;
	while (data->monster)
	{
		if (distance(list->x, list->y,
					data->monster->x, data->monster->y) < 1)
		{
			data->monster = head;
			explosions(data, list);
			list->dead = 1;
			break ;
		}
		data->monster = data->monster->next;
	}
	data->monster = head;
}

void			grenada(t_wolf *data)
{
	static int	delay = 0;
	t_object	*grenada;

	if (--delay < 0)
	{
	    if (!(grenada = (t_object *)ft_memalloc(sizeof(t_object))))
	    	clean_exit(data, "wolf3d: malloc error", 0);
	    grenada->i = data->player.pos;
	    grenada->x = data->player.x;
	    grenada->y = data->player.y;
	    grenada->type = 3;
	    grenada->si = 28;
	    grenada->sprite = data->sprite[grenada->si];
	    grenada->vx = cosf(data->player.angle);
	    grenada->vy = sinf(data->player.angle);
	    grenada->speed = 0.1f;
	    lst_pushback(data->object, grenada);
	    if (data->object == NULL)
	    	clean_exit(data, "wolf3d: malloc error", 0);
		delay = 20;
	}
}
