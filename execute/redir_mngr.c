/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_mngr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:57:40 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/05/05 12:05:35 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_inits(t_data *data, t_cmd *com, t_redir **redir, int *last)
{
	data->ret = 0;
	count_redir(com);
	*redir = malloc(com->n_redir * sizeof(t_redir));
	if (!*redir)
		ft_exit(data, com);
	last[0] = -1;
	last[1] = -1;
	data->std_out = 1;
	data->std_in = 0;
}

void	redirs_dups(t_data *data, int fdout, int fdin)
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
		redirs_dups(data, fdout, fdin);
		cmd_caller(com, data);
	}
}

void	redir_and_execute(t_data *data, t_cmd *com, t_redir *redir, int *last)
{
	int		status;
	int		i;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		do_redirs(data, com, redir, last);
		exit(data->ret);
	}
	else if (pid < 0)
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

/* last[0] contains the index of the last redir of < type
last[1] contains the index of the last redir of > or >> type */
void	redir_manager(t_cmd *com, t_data *data)
{
	int		i;
	t_redir	*redir;
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
	redir_and_execute(data, com, redir, last);
}
