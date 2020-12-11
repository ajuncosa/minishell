/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 14:06:41 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/01/28 13:19:44 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*copy;

	i = 0;
	copy = (char *)s;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (&copy[i]);
		i++;
	}
	if (s[i] == c)
		return (&copy[i]);
	else
		return (0);
}
