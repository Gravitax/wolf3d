/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 13:27:44 by maboye            #+#    #+#             */
/*   Updated: 2019/05/13 13:51:27 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft.h"

char			**ft_tabmerge(const char **t1, const char **t2)
{
	char	**ret;
	int		i;
	int		j;

	if ((t1 && !t2) || (!t1 && t2))
		return (t1 ? ft_tabdup(t1) : ft_tabdup(t2));
	else if (!t1 && !t2)
		return (NULL);
	i = -1;
	j = -1;
	if (!(ret = (char **)malloc(sizeof(char *)
			* (ft_tablen((void **)t1) + ft_tablen((void **)t2) + 1))))
		return (NULL);
	while (t1 && t1[++i])
		ret[i] = ft_strdup(t1[i]);
	while (t2 && t2[++j])
		ret[i++] = ft_strdup(t2[j]);
	ret[i] = NULL;
	return (ret);
}
