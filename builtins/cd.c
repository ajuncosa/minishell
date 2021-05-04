/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:49:48 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/05/04 13:34:44 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_dir(t_data *data, char *str)
{
	t_list	*list;

	list = data->env_head;
	while (list)
	{
		if (!ft_strcmp(((t_env *)list->content)->id, str))
		{
			free(((t_env *)list->content)->value);
			((t_env *)list->content)->value = getcwd(NULL, 0);
		}
		list = list->next;
	}
}

void	ft_cd(t_data *data, t_cmd *com)
{
	char	*path;
	char	*sterr;

	change_dir(data, "OLDPWD");
	if (com->args_str == NULL || !ft_strcmp(com->args_str[0], "~"))
	{
		path = ft_strjoin("/Users/", g_user);
		if (chdir(path) == -1)
		{
			sterr = strerror(errno);
			error_msn("cd", com->args_str[0], sterr);
		}
		free(path);
		data->ret = 0;
		return ;
	}
	if (chdir(com->args_str[0]) == -1)
	{
		sterr = strerror(errno);
		error_msn("cd", com->args_str[0], sterr);
		data->ret = 1;
		return ;
	}
	change_dir(data, "PWD");
	data->ret = 0;
}
