/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:12:20 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/01/10 16:27:22 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*tmps;

	i = 0;
	tmps = (char *)s;
	while (i < n)
	{
		if (tmps[i] == (char)c)
			return (&tmps[i]);
		i++;
	}
	return (0);
}
