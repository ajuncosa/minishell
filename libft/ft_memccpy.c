/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 16:15:42 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/05 13:50:55 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*tmpdst;
	unsigned const char	*tmpsrc;
	unsigned char		a;

	tmpdst = (unsigned char *)dst;
	tmpsrc = (unsigned const char *)src;
	a = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		tmpdst[i] = tmpsrc[i];
		if (tmpsrc[i] == a)
			return (&tmpdst[i + 1]);
		i++;
	}
	return (0);
}
