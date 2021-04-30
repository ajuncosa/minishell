/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_mngr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:57:40 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/04/30 18:51:05 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_manager(t_cmd *com, t_data *data)
{
	int		i;
	t_redir	*redir;
	int		fd;
	int		fdin;
	int		fdout;
	int		status;
	char	*sterr;
	int		last_in;
	int		last_out;

	data->ret = 0;
	count_redir(com);
	redir = malloc(com->n_redir * sizeof(t_redir));
	if (!redir)
		ft_exit(data, com);
	if (!arg_cleaner(com, redir))
		ft_exit(data, com);
	last_in = -1;
	last_out = -1;
	fdin = -1;
	fdout = -1;
	data->std_out = 1;
	data->std_in = 0;
	i = 0;
	while (i < com->n_redir)
	{
		if (!ft_strcmp(redir[i].type, ">"))
		{
			fd = open(redir[i].file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
			if (fd == -1)
			{
				sterr = strerror(errno);
				error_msn(redir[i].file, NULL, sterr);
				i = 0;
				while (i < com->n_redir)
				{
					free(redir[i].type);
					free(redir[i].file);
					i++;
				}
				free(redir);
				data->ret = 1;
				return ;
			}
			close(fd);
			last_out = i;
		}
		else if (!ft_strcmp(redir[i].type, ">>"))
		{
			fd = open(redir[i].file, O_WRONLY | O_APPEND | O_CREAT, 0777);
			if (fd == -1)
			{
				sterr = strerror(errno);
				error_msn(redir[i].file, NULL, sterr);
				i = 0;
				while (i < com->n_redir)
				{
					free(redir[i].type);
					free(redir[i].file);
					i++;
				}
				free(redir);
				data->ret = 1;
				return ;
			}
			close(fd);
			last_out = i;
		}
		else if (!ft_strcmp(redir[i].type, "<"))
		{
			fd = open(redir[i].file, O_RDONLY);
			if (fd == -1)
			{
				sterr = strerror(errno);
				error_msn(redir[i].file, NULL, sterr);
				i = 0;
				while (i < com->n_redir)
				{
					free(redir[i].type);
					free(redir[i].file);
					i++;
				}
				free(redir);
				data->ret = 1;
				return ;
			}
			close(fd);
			last_in = i;
		}
		i++;
	}
	g_pid = fork();
	if (g_pid == 0)
	{
		if (last_out != -1)
		{
			if (!ft_strcmp(redir[last_out].type, ">"))
				fdout = open(redir[last_out].file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
			else if (!ft_strcmp(redir[last_out].type, ">>"))
				fdout = open(redir[last_out].file, O_WRONLY | O_APPEND | O_CREAT, 0777);
		}
		if (last_in != -1)
			fdin = open(redir[last_in].file, O_RDONLY);
		if (com->cmd)
		{
			if (fdout != -1)
			{
				dup2(STDOUT_FILENO, data->std_out);
				dup2(fdout, STDOUT_FILENO);
				close(fdout);
			}
			if (fdin != -1)
			{
				dup2(fdin, STDIN_FILENO);
				close(fdin);
			}			
			cmd_caller(com, data);
		}
		exit(data->ret);
	}
	else if (g_pid < 0)
		fork_errors();
	wait(&status);
	data->ret = WEXITSTATUS(status);
	i = 0;
	while (i < com->n_redir)
	{
		free(redir[i].type);
		free(redir[i].file);
		i++;
	}
	free(redir);
}
