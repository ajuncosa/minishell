/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mngr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:05:03 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/04/30 17:39:28 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_caller(t_cmd *com, t_data *data, char **envp)
{
	int	len;

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

void	redirs_and_exec(t_data *data, t_cmd *com, char **envp)
{
	if (check_if_redir(com))
		redir_manager(com, data, envp);
	else
	{
		if (!create_args_str(com))
			ft_exit(data, com);
		cmd_caller(com, data, envp);
	}
}

void	handle_pipe_output(t_data *data, char **envp, t_cmd *com, int *fd_read)
{
	int		fd[2];
	int		status;

	pipe(fd);
	g_pid = fork();
	if (g_pid == 0)
	{
		if (*fd_read)
		{
			dup2(*fd_read, STDIN_FILENO);
			close(*fd_read);
		}
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		redirs_and_exec(data, com, envp);
		exit(data->ret);
	}
	else if (g_pid < 0)
		fork_errors();
	wait(&status);
	data->ret = WEXITSTATUS(status);
	if (*fd_read)
		close(*fd_read);
	*fd_read = fd[0];
	close(fd[1]);
}

void	handle_pipe_input(t_data *data, char **envp, t_cmd *com, int *fd_read)
{
	char	*sterr;
	int		status;

	g_pid = fork();
	if (g_pid == 0)
	{
		dup2(*fd_read, STDIN_FILENO);
		close(*fd_read);
		redirs_and_exec(data, com, envp);
		exit(data->ret);
	}
	else if (g_pid < 0)
		fork_errors();
	wait(&status);
	data->ret = WEXITSTATUS(status);
	close(*fd_read);
	*fd_read = 0;
}

void	cmd_manager(t_data *data, char **envp)
{
	int		fd_read;
	t_list	*lst;

	lst = data->cmd_head;
	fd_read = 0;
	while (lst)
	{
		if (((t_cmd *)lst->content)->sep_0 != '|'
			&& ((t_cmd *)lst->content)->sep_1 != '|')
			redirs_and_exec(data, (t_cmd *)lst->content, envp);
		if (((t_cmd *)lst->content)->sep_1 == '|')
			handle_pipe_output(data, envp, (t_cmd *)lst->content, &fd_read);
		else if (((t_cmd *)lst->content)->sep_0 == '|')
			handle_pipe_input(data, envp, (t_cmd *)lst->content, &fd_read);
		lst = lst->next;
	}
}
