/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:29:59 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/01/10 17:32:07 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*tmps1;
	char	*tmps2;
	size_t	i;

	tmps1 = (char *)s1;
	tmps2 = (char *)s2;
	i = 0;
	while (i < n)
	{
		if (tmps1[i] != tmps2[i])
			return ((unsigned char)tmps1[i] - (unsigned char)tmps2[i]);
		i++;
	}
	return (0);
}
