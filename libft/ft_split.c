/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:30:48 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/05 13:52:50 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_pieces(char const *s, char c)
{
	size_t	i;
	size_t	count;
	size_t	len;

	i = 0;
	count = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		while (s[i] == c && i < len)
			i++;
		if (i != len)
		{
			while (s[i] != c && i < len)
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
	size_t	len_s;

	i = 0;
	y = 0;
	len_s = ft_strlen(s);
	while (y <= piece)
	{
		len = 0;
		while (s[i] == c && i < len_s)
			i++;
		while (s[i] != c && i < len_s)
		{
			len++;
			i++;
		}
		y++;
	}
	return (len);
}

static void	ft_fill_str(char *tab, char const *s, char c, size_t piece)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(s);
	while (j < piece)
	{
		while (s[i] == c && i < len)
			i++;
		while (s[i] != c && i < len)
			i++;
		j++;
	}
	while (s[i] == c && i < len)
		i++;
	j = 0;
	while (s[i] != c && i < len)
	{
		tab[j] = s[i];
		i++;
		j++;
	}
	tab[j] = '\0';
}

char	**ft_split(char const *s, char c)
{
	size_t	pieces;
	size_t	len;
	size_t	i;
	char	**tab;

	if (s == 0)
		return (NULL);
	pieces = ft_count_pieces(s, c);
	tab = malloc((pieces + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < pieces)
	{
		len = ft_len_pieces(s, c, i);
		tab[i] = malloc((len + 1) * sizeof(char));
		if (!tab[i])
			return (NULL);
		ft_fill_str(tab[i], s, c, i);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
