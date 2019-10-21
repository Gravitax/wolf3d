/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabaddelem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:33:03 by maboye            #+#    #+#             */
/*   Updated: 2019/05/13 13:44:00 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft.h"

char			**ft_tabaddelem(char **add, const char *str)
{
	int		i;
	char	**ret;

	if (!(ret = malloc(sizeof(char *) * (ft_tablen((void **)add) + 2))))
		return (NULL);
	i = -1;
	while (add && add[++i])
		if (!(ret[i] = ft_strdup(add[i])))
		{
			ft_tabfree((void **)ret);
			ft_tabfree((void **)add);
			return (NULL);
		}
	if ((ret[i++] = ft_strdup(str)))
		ret[i] = NULL;
	else
		ft_tabfree((void **)ret);
	ft_tabfree((void **)add);
	return (ret);
}
