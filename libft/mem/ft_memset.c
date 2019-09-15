/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:46:14 by maboye            #+#    #+#             */
/*   Updated: 2019/05/04 13:36:33 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void		*ft_memset(void *s, int c, size_t n)
{
	char	*ptr;
	size_t	i;

	if (!s)
		return (NULL);
	ptr = s;
	i = -1;
	while (++i < n)
		ptr[i] = c;
	return (s);
}
