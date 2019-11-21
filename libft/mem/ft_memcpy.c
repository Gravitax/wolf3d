/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:46:05 by maboye            #+#    #+#             */
/*   Updated: 2019/05/03 16:39:06 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void		*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dptr;
	unsigned char	*sptr;

	if (!dest || !src)
		return ((void *)0);
	dptr = (unsigned char *)dest;
	sptr = (unsigned char *)src;
	while (n--)
		*dptr++ = *sptr++;
	return (dest);
}
