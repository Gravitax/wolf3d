/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:05:22 by maboye            #+#    #+#             */
/*   Updated: 2019/08/29 15:08:19 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void            lst_free(t_object *list)
{
    t_object   *tmp;

    while (list)
    {
        tmp = list->next;
        ft_memdel((void **)&list);
        if (tmp)
            list = tmp;
    }
}

int             lst_len(t_object *list)
{
    int         i;
    t_object    *tmp;

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

void            lst_pushback(t_object *list)
{
    t_object    *head;

    head = list;
    if (list)
    {
        while (list->next)
            list = list->next;
        if (!(list->next = (t_object *)ft_memalloc(sizeof(t_object))))
        {
            lst_free(head);
            return ;
        }
    }
    list = head;
}
