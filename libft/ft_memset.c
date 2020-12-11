/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:53:46 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/01/09 16:15:11 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*tmpb;

	tmpb = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		tmpb[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
