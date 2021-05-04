/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:38:41 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/05/04 13:42:43 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
