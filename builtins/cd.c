/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:49:48 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/05/05 13:16:59 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_envdir(t_data *data, char *str)
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

void	go_home(t_data *data)
{
	char	*path;
	char	*sterr;

	path = is_in_env(&data->env_head, "HOME");
	if (!path)
	{
		error_msn("cd", NULL, "HOME not set");
		data->ret = 1;
	}
	else if (chdir(path) == -1)
	{
		sterr = strerror(errno);
		error_msn("cd", NULL, sterr);
		data->ret = 0;
	}
}

void	ft_cd(t_data *data, t_cmd *com)
{
	char	*sterr;

	change_envdir(data, "OLDPWD");
	if (com->args_str == NULL || !ft_strcmp(com->args_str[0], "~"))
	{
		go_home(data);
		return ;
	}
	if (chdir(com->args_str[0]) == -1)
	{
		sterr = strerror(errno);
		error_msn("cd", com->args_str[0], sterr);
		data->ret = 1;
		return ;
	}
	change_envdir(data, "PWD");
	data->ret = 0;
}
