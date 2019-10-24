/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:46:29 by maboye            #+#    #+#             */
/*   Updated: 2019/08/23 10:31:45 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char		*ft_strdup(const char *src)
{
	int		len;
	char	*copy;

	len = ft_strlen(src);
	if (!(copy = ft_strnew(len)))
		return ((void *)0);
	ft_strcpy(copy, src);
	return (copy);
}
