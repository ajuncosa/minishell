/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_utils_libft.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 09:44:28 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/05/03 09:44:57 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (!str)
		return (NULL);
	copy = malloc(sizeof(t_letter) * (esc_strlen(str) + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (str[i].c != '\0')
	{
		copy[i] = str[i];
		i++;
	}
	copy[i].c = '\0';
	return (copy);
}

t_letter	*esc_join(t_letter *s1, t_letter *s2)
{
	t_letter	*new;
	size_t		i;
	size_t		j;

	if (!s1 || !s2)
		return (NULL);
	new = malloc(sizeof(t_letter) * (esc_strlen(s1) + esc_strlen(s2) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j].c != '\0')
		new[i++] = s1[j++];
	j = 0;
	while (s2[j].c != '\0')
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
	if (str[0].c == '\0' || start > esc_strlen(str))
	{
		new[0].c = '\0';
		new[0].esc = 0;
		return (new);
	}
	new = malloc((len + 1) * sizeof(t_letter));
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
