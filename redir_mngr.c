/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_mngr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:57:40 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/05/03 14:03:00 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_open_error(t_data *data, t_redir *redir, int i, int n_redir)
{
	char	*sterr;

	sterr = strerror(errno);
	error_msn(redir[i].file, NULL, sterr);
	i = 0;
	while (i < n_redir)
	{
		free(redir[i].type);
		free(redir[i].file);
		i++;
	}
	free(redir);
	data->ret = 1;
}

int	redir_open_files(t_data *data, t_redir redir, int *last, int i)
{
	int	fd;

	if (!ft_strcmp(redir.type, ">"))
	{
		last[1] = i;
		fd = open(redir.file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	}
	else if (!ft_strcmp(redir.type, ">>"))
	{
		last[1] = i;
		fd = open(redir.file, O_WRONLY | O_APPEND | O_CREAT, 0777);
	}
	else if (!ft_strcmp(redir.type, "<"))
	{
		last[0] = i;
		fd = open(redir.file, O_RDONLY);
	}
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

void	redir_inits(t_data *data, t_cmd *com, t_redir **redir, int *last)
{
	data->ret = 0;
	count_redir(com);
	*redir = malloc(com->n_redir * sizeof(t_redir));
	if (!redir)
		ft_exit(data, com);
	last[0] = -1;
	last[1] = -1;
	data->std_out = 1;
	data->std_in = 0;
}

void	do_redirs(t_data *data, t_cmd *com, t_redir *redir, int *last)
{
	int		fdin;
	int		fdout;
	char	*last_out_file;
	char	*last_in_file;

	fdin = -1;
	fdout = -1;
	last_out_file = redir[last[1]].file;
	last_in_file = redir[last[0]].file;
	if (last[1] != -1)
	{
		if (!ft_strcmp(redir[last[1]].type, ">"))
			fdout = open(last_out_file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		else if (!ft_strcmp(redir[last[1]].type, ">>"))
			fdout = open(last_out_file, O_WRONLY | O_APPEND | O_CREAT, 0777);
	}
	if (last[0] != -1)
		fdin = open(last_in_file, O_RDONLY);
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
}

/* last[0] contains the index of the last redir of < type
last[1] contains the index of the last redir of > or >> type */
void	redir_manager(t_cmd *com, t_data *data)
{
	int		i;
	t_redir	*redir;
	int		status;
	int		last[2];

	redir_inits(data, com, &redir, last);
	if (!arg_cleaner(com, redir))
		ft_exit(data, com);
	i = 0;
	while (i < com->n_redir)
	{		
		if (!redir_open_files(data, redir[i], last, i))
		{
			redir_open_error(data, redir, i, com->n_redir);
			return ;
		}
		i++;
	}
	g_pid = fork();
	if (g_pid == 0)
	{
		do_redirs(data, com, redir, last);
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
