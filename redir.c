/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:57:40 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/04/23 15:22:31 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_if_redir(t_cmd *com)
{
	int		i;
	char	*arg;

	i = 0;
	while (i < com->n_args)
	{
		arg = struct_to_str(com->args[i], 0, esc_strlen(com->args[i]));
		if ((!ft_strcmp(arg, ">") || !ft_strcmp(arg, ">>") || !ft_strcmp(arg, "<")) && !com->args[i][0].esc)
		{
			free(arg);
		    return (1);
		}
		free(arg);
		i++;
	}
	return (0);
}

void		count_redir(t_cmd *com)
{
	int		i;
	char	*arg;

	i = 0;
	com->n_redir = 0;
	while (i < com->n_args)
	{
		arg = struct_to_str(com->args[i], 0, esc_strlen(com->args[i]));
		if ((!ft_strcmp(arg, ">") || !ft_strcmp(arg, ">>") || !ft_strcmp(arg, "<")) && !com->args[i][0].esc)
		    com->n_redir++;
		free(arg);
		i++;
	}
}

int		arg_cleaner(t_cmd *com, t_redir *redir)
{
	int		i;
	int		j;
	int		k;
	int		n_del;
	char	*arg;

	n_del = com->n_redir * 2;
	if ((com->n_args - n_del) > 0)
	{
		com->args_str = malloc((com->n_args - n_del)  * sizeof(char *));
		if (!com->args_str)
			return (0);
	}
	i = 0;
	j = 0;
	k = 0;
	while (i < com->n_args)
	{
		arg = struct_to_str(com->args[i], 0, esc_strlen(com->args[i]));
		if ((!ft_strcmp(arg, ">") || !ft_strcmp(arg, ">>") || !ft_strcmp(arg, "<")) && !com->args[i][0].esc)
		{
			redir[k].type = ft_strdup(arg);
			if (!redir[k].type)
				return (0);
			free(arg);
			arg = struct_to_str(com->args[i + 1], 0, esc_strlen(com->args[i + 1]));
			redir[k].file = ft_strdup(arg);
			if (!redir[k].file)
				return (0);
			free(com->args[i]);
			k++;
			i++;
		}
		else 
		{
			com->args_str[j] = ft_strdup(arg);
			if (!com->args_str[j])
				return(0);
			j++;
		}
		free(com->args[i]);
		free(arg);
		i++;
	}
	free(com->args);
	com->args = NULL;
	com->n_args = com->n_args - n_del;
	return(1);
}

void	redir_manager(t_cmd *com, t_data *data, char **envp)
{
	int		i;
	t_redir	*redir;
	int     fd;
	int 	fdin;
	int		fdout;
	//int     pid;
	//int		r;
	int		status;
	char 	*sterr;
	int		last_in;
	int		last_out;

	data->ret = 0;
	count_redir(com);
	//printf("n_redir: %d\n", com->n_redir);
	redir = malloc(com->n_redir * sizeof(t_redir));
	if (!redir)
		ft_exit(data, com);
	if (!arg_cleaner(com, redir))
		ft_exit(data, com);
	/*i = 0;
	while (i < com->n_args)
	{
		printf("post-clean arg[%d]: %s\n", i, com->args_str[i]);
		i++;
	}*/
	/*i = 0;
	while (i < com->n_redir)
	{
		printf("type: %s, file: %s\n", redir[i].type, redir[i].file);
		i++;
	}*/
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
			fd = open(redir[i].file, O_WRONLY |  O_TRUNC | O_CREAT, 0777);
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
			fd = open(redir[i].file, O_WRONLY |  O_APPEND | O_CREAT, 0777);
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
	pid = fork();
	if (pid == 0)
	{
		if (last_out != -1)
		{
			if (!ft_strcmp(redir[last_out].type, ">"))
				fdout = open(redir[last_out].file, O_WRONLY |  O_TRUNC | O_CREAT, 0777);
			else if (!ft_strcmp(redir[last_out].type, ">>"))
				fdout = open(redir[last_out].file, O_WRONLY |  O_APPEND | O_CREAT, 0777);
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
			cmd_caller(com, data, envp);
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
	i = 0;
	while (i < com->n_redir)
	{
		free(redir[i].type);
		free(redir[i].file);
		i++;
	}
	free(redir);
}
