/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:38:41 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/04/20 14:15:45 by ajuncosa         ###   ########.fr       */
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
			while (str[i] != '\'' && str[i] != '\0')
			{
				i++;
				n++;
			}
			if (str[i] == '\'')
				i++;
			continue ;
		}
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' && str[i] != '\0')
			{
				if (str[i] == '\\' && (str[i + 1] == '$' || str[i + 1] == '"' || str[i + 1] == '\\'))
				{
					i++;
					if (str[i] == '\0')
						return (n);
				}
				i++;
				n++;
			}
			if (str[i] == '"')
				i++;
			continue ;
		}
		if (str[i] == '\\')
		{
			i++;
			if (str[i] == '\0')
			{
				write(2, "Error: open backslash\n", 23);
				return (-1);
			}
		}
		n++;
		i++;
	}
	return (n);
}
/*
int	esc_strlen(t_letter *str) 
{
	int	i;

	i = 0;
	while (str[i].c != '\0')
		i++;
	return (i);
}

t_letter	*esc_dup(t_letter *str)
{
	size_t		i;
	t_letter	*copy;

	if (!s1)
		return (NULL);
	copy = malloc((esc_strlen(str) + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (str[i].c != '\0')
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i].c = '\0';
	return (copy);	
}

t_letter	*esc_join(t_letter *s1, t_letter *s2)
{
	t_letter	*new;
	size_t	i;
	size_t	j;

	if (!s1)
		return (NULL);
	new = malloc(sizeof(t_letter) * (esc_strlen(s1) + esc_strlen(s2) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i].c != '\0')
		new[i++] = s1[j++];
	while (s2[i].c != '\0')
		new[i++] = s2[j++];
	new[i].c = '\0';
	return (new);
}

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
}*/
