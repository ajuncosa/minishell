/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:49:48 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/01/28 12:31:56 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_cd(char *str, char *user)
{   
	char	*trimmed;
	char	*sterr;
	char	*path;
	int 	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\n')
	{
		path = ft_strjoin("/Users/", user);
		chdir(path);
		free(path);
		return ;
	}
	trimmed = ft_strtrim(&str[i], " \n");
	if (chdir(trimmed) == -1)
	{
		sterr = strerror(errno);
		write(1, sterr, ft_strlen(sterr));
		write(1, "\n", 1);
	}
}
