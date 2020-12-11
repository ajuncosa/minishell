/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:30:48 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/02/11 12:54:56 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_pieces(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (i < ft_strlen(s))
	{
		while (s[i] == c && i < ft_strlen(s))
			i++;
		if (i != ft_strlen(s))
		{
			while (s[i] != c && i < ft_strlen(s))
				i++;
			count++;
		}
	}
	return (count);
}

static size_t	ft_len_pieces(char const *s, char c, size_t piece)
{
	size_t	len;
	size_t	y;
	size_t	i;

	i = 0;
	y = 0;
	while (y <= piece)
	{
		len = 0;
		while (s[i] == c && i < ft_strlen(s))
			i++;
		while (s[i] != c && i < ft_strlen(s))
		{
			len++;
			i++;
		}
		y++;
	}
	return (len);
}

static void		ft_fill_str(char *tab, char const *s, char c, size_t piece)
{
	size_t	y;
	size_t	i;
	size_t	j;

	i = 0;
	y = 0;
	j = 0;
	while (y < piece)
	{
		while (s[i] == c && i < ft_strlen(s))
			i++;
		while (s[i] != c && i < ft_strlen(s))
			i++;
		y++;
	}
	while (s[i] == c && i < ft_strlen(s))
		i++;
	while (s[i] != c && i < ft_strlen(s))
	{
		tab[j] = s[i];
		i++;
		j++;
	}
	tab[j] = '\0';
}

char			**ft_split(char const *s, char c)
{
	size_t	pieces;
	size_t	len;
	size_t	i;
	char	**tab;

	if (s == 0)
		return (NULL);
	pieces = ft_count_pieces(s, c);
	if (!(tab = malloc((pieces + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	while (i < pieces)
	{
		len = ft_len_pieces(s, c, i);
		if (!(tab[i] = malloc((len + 1) * sizeof(char))))
			return (NULL);
		ft_fill_str(tab[i], s, c, i);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
