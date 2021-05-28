/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:07:29 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/05/28 15:04:37 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signals_fork(int sig)
{
	if (sig == SIGQUIT)
		write(1, "\b\b  \b\b", 6);
	else if (sig == SIGINT)
		write(1, "\b\b  \b\b\n", 7);
}

void	handle_pipe_output(t_data *data, t_cmd *com, int *fd, int *fd_read)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (*fd_read)
		{
			dup2(*fd_read, STDIN_FILENO);
			close(*fd_read);
		}
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		redirs_and_exec(data, com);
		exit(data->ret);
	}
	else if (pid < 0)
		fork_errors();
	data->n_waits++;
	if (*fd_read)
		close(*fd_read);
	*fd_read = fd[0];
	close(fd[1]);
}

void	handle_pipe_input(t_data *data, t_cmd *com, int *fd_read)
{
	pid_t	pid;	

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, signals_fork);
		signal(SIGQUIT, signals_fork);
		dup2(*fd_read, STDIN_FILENO);
		close(*fd_read);
		redirs_and_exec(data, com);
		exit(data->ret);
	}
	else if (pid < 0)
		fork_errors();
	data->n_waits++;
	data->last_pipe_pid = pid;
	close(*fd_read);
	*fd_read = 0;
}

void	pipes_waits(t_data *data)
{
	int	status;
	int	i;

	i = 0;
	waitpid(data->last_pipe_pid, &status, 0);
	data->ret = WEXITSTATUS(status);
	while (i < data->n_waits - 1)
	{
		wait(NULL);
		i++;
	}
	data->n_waits = 0;
}
