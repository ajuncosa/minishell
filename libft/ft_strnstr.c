/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 15:28:37 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/05 14:08:34 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	char	*hay;

	i = 0;
	hay = (char *)haystack;
	if (needle[0] == '\0')
		return (hay);
	while (haystack[i] != '\0' && i < len)
	{
		if (!(ft_strncmp(&haystack[i], needle, ft_strlen(needle))))
		{
			if (ft_strlen(needle) > (len - i))
				return (NULL);
			return (&hay[i]);
		}
		i++;
	}
	return (NULL);
}
