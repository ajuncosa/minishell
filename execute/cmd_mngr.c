/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mngr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:05:03 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/05/28 15:01:00 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_caller(t_cmd *com, t_data *data)
{
	int	len;

	len = ft_strlen(com->cmd);
	if (!ft_strcmp(com->cmd, "echo"))
		ft_echo(data, com);
	else if (!ft_strcmp(com->cmd, "pwd"))
		ft_pwd(data);
	else if (!ft_strcmp(com->cmd, "export"))
		ft_export(data, com);
	else if (!ft_strcmp(com->cmd, "cd"))
		ft_cd(data, com);
	else if (!ft_strcmp(com->cmd, "unset"))
		ft_unset(data, com);
	else if (!ft_strcmp(com->cmd, "env"))
		ft_env(data, com->args_str);
	else if (!ft_strcmp(com->cmd, "exit"))
		ft_exit(data, com);
	else
		ft_cmd(com, data);
}

void	redirs_and_exec(t_data *data, t_cmd *com)
{
	if (check_if_redir(com))
		redir_manager(com, data);
	else
	{
		if (!create_args_str(com))
			ft_exit(data, com);
		cmd_caller(com, data);
	}
}

void	cmd_manager(t_data *data)
{
	int		fd[2];
	int		fd_read;
	t_list	*lst;

	lst = data->cmd_head;
	fd_read = 0;
	while (lst)
	{
		data->last_pipe_pid = 0;
		if (((t_cmd *)lst->content)->sep_0 != '|'
			&& ((t_cmd *)lst->content)->sep_1 != '|')
			redirs_and_exec(data, (t_cmd *)lst->content);
		if (((t_cmd *)lst->content)->sep_1 == '|')
		{
			pipe(fd);
			handle_pipe_output(data, (t_cmd *)lst->content, fd, &fd_read);
		}
		else if (((t_cmd *)lst->content)->sep_0 == '|')
			handle_pipe_input(data, (t_cmd *)lst->content, &fd_read);
		if (data->last_pipe_pid && (((t_cmd *)lst->content)->sep_1 == ';'
				|| ((t_cmd *)lst->content)->sep_1 == '0'))
			pipes_waits(data);
		lst = lst->next;
	}
}
