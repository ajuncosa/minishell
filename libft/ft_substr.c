/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 09:37:49 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/01/15 14:18:25 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*new;

	if (s == 0)
		return (0);
	if (*s == '\0')
		return (ft_strdup(""));
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (!(new = malloc(len + 1)))
		return (0);
	i = start;
	j = 0;
	while (i < (len + start))
	{
		new[j] = s[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (new);
}
