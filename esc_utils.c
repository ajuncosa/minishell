/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:38:41 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/04/20 11:53:24 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	esc_size(char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			n++;
			while (str[i] != '\'' && str[i] != '\0')
			{
				i++;
				n++;
			}
		}
		if (str[i] == '\\')
			i++;
		if (str[i])
			n++;
		i++;
	}
	return (n);
}

int	esc_strlen(t_letter *str) 
{
	int	i;

	i = 0;
	while (str[i].c != '\0')
		i++;
	return (i);
}

t_letter	esc_dup

t_letter	*esc_substr(t_letter *str, unsigned int start, size_t len)
{
	size_t		i;
	size_t		j;
	t_letter	*new;

	if (!str)
		return (NULL);
	if (str[0].c == '\0')
		return (esc_dup(""));
	if (start > esc_strlen(str))
		return (esc_dup(""));
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	i = start;
	j = 0;
	while (i < (len + start))
	{
		new[j] = str[i];
		i++;
		j++;
	}
	new[j].c = '\0';
	return (new);
}
