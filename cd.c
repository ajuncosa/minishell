/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:49:48 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/08 11:56:48 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ft_cd(t_cmd *com, char *user)
{   
	//TODO: return $?
	char	*sterr;
	char	*path;
	
	if (com->args == NULL)
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
	if (com->n_args > 1)
	{
		write(1, "cd: string not in pwd: ", 24);
		write(1, com->args[0], ft_strlen(com->args[0]));
		write(1, "\n", 1);
	}
	if (chdir(com->args[0]) == -1)
	{
		sterr = strerror(errno);
		write(1, sterr, ft_strlen(sterr));
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}
