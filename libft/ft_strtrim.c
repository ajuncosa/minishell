/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 11:57:14 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/05 14:03:56 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*new;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	start = 0;
	while (ft_strchr(set, s1[start]) && start < len)
		start++;
	if (start == len)
	{
		return (ft_strdup(""));
	}
	end = len - 1;
	while (ft_strchr(set, s1[end]) && end >= start)
		end--;
	new = ft_substr(s1, start, end - start + 1);
	return (new);
}
