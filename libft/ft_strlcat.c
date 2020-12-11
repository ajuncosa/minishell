/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 09:41:32 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/01/09 12:53:37 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dstlen1;

	dstlen1 = ft_strlen(dst);
	if (dstsize == 0)
		return (ft_strlen(src));
	if (dstlen1 > dstsize)
		return (dstsize + ft_strlen(src));
	i = 0;
	j = 0;
	while (dst[i] != '\0')
		i++;
	while (src[j] != '\0' && i < (dstsize - 1))
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dstlen1 + ft_strlen(src));
}
