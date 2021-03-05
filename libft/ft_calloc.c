/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 17:32:35 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/05 13:44:39 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*s;
	size_t	i;

	s = malloc(count * size);
	if (!s)
		return (0);
	i = 0;
	while (i < (count * size))
	{
		s[i] = 0;
		i++;
	}
	return (s);
}
