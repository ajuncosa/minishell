/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:49:48 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/01/29 12:43:41 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ft_cd(char *str, char *user)
{   
	char	*trimmed;						//TODO: return $?
	char	*sterr;
	char	*path;
	int 	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\n')
	{
		path = ft_strjoin("/Users/", user);
		if (chdir(path) == -1)
		{
			sterr = strerror(errno);
			write(1, sterr, ft_strlen(sterr));
			write(1, "\n", 1);
		}
		free(path);
		return (0);
	}
	trimmed = ft_strtrim(&str[i], " \n");
	if (chdir(trimmed) == -1)
	{
		sterr = strerror(errno);
		write(1, sterr, ft_strlen(sterr));
		write(1, "\n", 1);
		free (trimmed);
		return (1);
	}
	free (trimmed);
	return (0);
}
