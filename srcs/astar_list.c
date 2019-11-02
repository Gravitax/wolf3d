/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:30:54 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void            alst_free(t_lst *list)
{
    t_lst   *tmp;

    while (list)
    {
        tmp = list->next;
        ft_memdel((void **)&list);
        if (tmp)
            list = tmp;
    }
}

int             alst_len(t_lst *list)
{
    int     i;
    t_lst   *tmp;

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

void            alst_pushback(t_lst *list, t_node *node)
{
    t_lst   *head;

    head = list;
    if (list)
    {
        while (list->next)
            list = list->next;
        if (!(list->next = (t_lst *)ft_memalloc(sizeof(t_lst))))
        {
            alst_free(head);
            return ;
        }
        list->next->node = node;
    }
    list = head;
}

static void     alst_swap(t_lst *a, t_lst *b)
{
    t_node  *tmp;

    tmp = b->node;
	b->node = a->node;
    a->node = tmp;
}

void			alst_sort(t_lst *list)
{
	t_lst		*tmp;
	int			sorted;

	if (list == NULL)
		return ;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		tmp = list;
		while (tmp->next)
		{
			if (tmp->node->globalgoal > tmp->next->node->globalgoal)
			{
				alst_swap(tmp, tmp->next);
				sorted = 0;
			}
		    tmp = tmp->next;
		}
	}
}
