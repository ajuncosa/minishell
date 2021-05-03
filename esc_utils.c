/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:38:41 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/05/03 09:37:34 by ajuncosa         ###   ########.fr       */
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

char	*struct_to_str(t_letter *struc, int start, int len)
{
	int		i;
	int		j;
	char	*str;

	if (!struc)
		return (NULL);
	if (struc[0].c == '\0')
		return (ft_strdup(""));
	if (start > esc_strlen(struc))
		return (ft_strdup(""));
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = start;
	j = 0;
	while (i < (len + start))
	{
		str[j] = struc[i].c;
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

t_letter	*str_to_struct(char *str)
{
	int			i;
	t_letter	*new;

	if (!str)
		return (NULL);
	new = malloc(sizeof(t_letter) * (ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new[i].c = str[i];
		new[i].esc = 1;
		i++;
	}
	new[i].c = '\0';
	return (new);
}

int	is_escapable(char c, int quote)
{
	if (!quote || (quote == 2 && (c == '$' || c == '\\' || c == '"')))
		return (1);
	return (0);
}
