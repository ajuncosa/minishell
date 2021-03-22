/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:49:48 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/22 12:36:08 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ft_cd(t_cmd *com, char *user, t_list **env_head)
{   
	//TODO: return $?
	char	*path;
	t_list	*list;
	char	*sterr;

	list = *env_head;
	while (list)
	{
		if (!ft_strcmp(((t_env*)list->content)->id, "OLDPWD"))
		{
			free(((t_env*)list->content)->value);
			((t_env*)list->content)->value = getcwd(NULL, 0);
		}
		list = list->next;
	}
	if (com->args == NULL)
	{
		path = ft_strjoin("/Users/", user);
		if (chdir(path) == -1)
		{
			sterr = strerror(errno);
			write(2, sterr, ft_strlen(sterr));
			write(2, "\n", 1);
		}
		free(path);
		return (0);
	}
	if (chdir(com->args[0]) == -1)
	{
		sterr = strerror(errno);
		write(2, sterr, ft_strlen(sterr));
		write(2, "\n", 1);
		return (1);
	}
	list = *env_head;
	while (list)
	{
		if (!ft_strcmp(((t_env*)list->content)->id, "PWD"))
		{
			free(((t_env*)list->content)->value);
			((t_env*)list->content)->value = getcwd(NULL, 0);
		}
		list = list->next;
	}
	return (0);
}
