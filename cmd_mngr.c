/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mngr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:05:03 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/04/28 12:05:23 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_caller(t_cmd *com, t_data *data, char **envp)
{
	int len;

	len = ft_strlen(com->cmd);
	if (!ft_strcmp(com->cmd, "echo"))
		ft_echo(data, com);
	else if (!ft_strcmp(com->cmd, "pwd"))
		ft_pwd(data, com->args_str);
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
		ft_cmd(com, envp, data);
}

void	cmd_manager(t_data *data, char **envp)
{
	int		fd[2];
	int		fd_read;
	t_list	*lst;
	char	*sterr;
	int		status;

	lst = data->cmd_head;
	fd_read = 0;
	while (lst)
	{
		if (((t_cmd*)lst->content)->sep_0 != '|' && ((t_cmd*)lst->content)->sep_1 != '|')
		{
			if (check_if_redir(((t_cmd*)lst->content)))
				redir_manager(((t_cmd*)lst->content), data, envp);
			else
			{
				if (!create_args_str((t_cmd*)lst->content))
					ft_exit(data, (t_cmd*)lst->content);
				cmd_caller(((t_cmd*)lst->content), data, envp);
			}
		}
		if (((t_cmd*)lst->content)->sep_1 == '|')
		{
			pipe(fd);
			pid = fork();
			if (pid == 0)
			{
				if (fd_read)
				{
					dup2(fd_read, STDIN_FILENO);
					close(fd_read);
				}
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				if (check_if_redir(((t_cmd*)lst->content)))
					redir_manager(((t_cmd*)lst->content), data, envp);
				else
				{
					if (!create_args_str((t_cmd*)lst->content))
						ft_exit(data, (t_cmd*)lst->content);
					cmd_caller(((t_cmd*)lst->content), data, envp);
				}
				exit(data->ret);
			}
			else if (pid < 0)
			{
				sterr = strerror(errno);
				error_msn(NULL, NULL, sterr);
			}
			wait(&status);
			data->ret = WEXITSTATUS(status);
			if (fd_read)
				close(fd_read);
			fd_read = fd[0];
			close(fd[1]);
		}
		else if (((t_cmd*)lst->content)->sep_0 == '|')
		{
			pid = fork();
			if (pid == 0)
			{
				dup2(fd_read, STDIN_FILENO);
				close(fd_read);
				if (check_if_redir(((t_cmd*)lst->content)))
					redir_manager(((t_cmd*)lst->content), data, envp);
				else
				{
					if (!create_args_str((t_cmd*)lst->content))
						ft_exit(data, (t_cmd*)lst->content);
					cmd_caller(((t_cmd*)lst->content), data, envp);
				}
				exit(data->ret);
			}
			else if (pid < 0)
			{
				sterr = strerror(errno);
				error_msn(NULL, NULL, sterr);
			}
			wait(&status);
			data->ret = WEXITSTATUS(status);
			close(fd_read);
			fd_read = 0;
		}
		lst = lst->next;
	}
}
