/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:57:40 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/03/22 12:53:16 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_if_redir(t_cmd *com)
{
	int	i;

	i = 0;
	while (i < com->n_args)
	{
		if (!ft_strcmp(com->args[i], ">") || !ft_strcmp(com->args[i], ">>") 
		|| !ft_strcmp(com->args[i], "<"))
		    return (1);
		i++;
	}
	return (0);
}

char	**arg_cleaner(t_cmd *com, t_redir **redir)
{
	char	**new;
	int		i;
	int		j;
	int		k;
	int		n_del;
	//contar nargs a borrar
	i = 0;
	n_del = 0;
	while (i < com->n_args)
	{
		if (!ft_strcmp(com->args[i], ">") || !ft_strcmp(com->args[i], ">>") 
		|| !ft_strcmp(com->args[i], "<"))
		    n_del += 2;
		i++;
	}
	com->n_redir = n_del / 2;
	//crear nueva string y array de redirs
	new = malloc((com->n_args - n_del)  * sizeof(char *));
	if (!new)
		return (NULL);
	*redir = malloc(com->n_redir * sizeof(t_redir));
	if (!*redir)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	while (i < com->n_args)
	{
		if (!ft_strcmp(com->args[i], ">") || !ft_strcmp(com->args[i], ">>") 
		|| !ft_strcmp(com->args[i], "<"))
		{
			(*redir[k]).type = ft_strdup(com->args[i]);
			if (!(*redir[k]).type)
				return (NULL);
			(*redir[k]).file = ft_strdup(com->args[i + 1]);
			if (!(*redir[k]).file)
				return (NULL);
			k++;
			i++;
		}
		else 
		{
			new[j] = ft_strdup(com->args[i]);
			if (!new[j])
				return(NULL);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < com->n_args)
	{
		free(com->args[i]);
		i++;
	}
	com->n_args = com->n_args - n_del;
	return(new);
}

int redir_manager(t_cmd *com, t_list **env_head, t_list **cmd_head, int ret, char *user, char **envp)
{
	char	**new;
	int		i;
	t_redir	*redir;
	int     fd;
	int     pid;
	int		r;
	char 	*sterr;

	new = arg_cleaner(com, &redir);
	if (!new)
		ft_exit(env_head, cmd_head, user);
	free(com->args);
	com->args = new;

	i = 0; //TODO: cuando le pasas varias redirecciones

	if (!ft_strcmp(redir[i].type, ">"))
	{
		pid = fork();
		if (pid == 0)
		{
			fd = open(redir[i].file, O_WRONLY |  O_TRUNC | O_CREAT, 0777);
			if (fd == -1)
			{
				sterr = strerror(errno);
				write(2, sterr, ft_strlen(sterr));
				write(2, "\n", 1);
			}
			if (com->cmd)
			{
				dup2(fd, STDOUT_FILENO);
				close(fd);
				r = cmd_caller(com, env_head, cmd_head, ret, user, envp);
			}
			exit(0);
		}
		else if (pid < 0)
		{
			sterr = strerror(errno);
			write(2, sterr, ft_strlen(sterr));
			write(2, "\n", 1);
		}
		wait(NULL);
	}
	else if (!ft_strcmp(redir[i].type, ">>"))
	{
		pid = fork();
		if (pid == 0)
		{
			fd = open(redir[i].file, O_WRONLY |  O_APPEND | O_CREAT, 0777);
			if (fd == -1)
			{
				sterr = strerror(errno);
				write(2, sterr, ft_strlen(sterr));
				write(2, "\n", 1);
			}
			if (com->cmd)
			{
				dup2(fd, STDOUT_FILENO);
				close(fd);
				r = cmd_caller(com, env_head, cmd_head, ret, user, envp);
			}
			exit(0);
		}
		else if (pid < 0)
		{
			sterr = strerror(errno);
			write(2, sterr, ft_strlen(sterr));
			write(2, "\n", 1);
		}
		wait(NULL);
	}
	else if (!ft_strcmp(redir[i].type, "<"))  //FIXME: cuando no existe el archivo
	{
		pid = fork();
		if (pid == 0)
		{
			fd = open(redir[i].file, O_RDONLY);
			if (fd == -1)
			{
				sterr = strerror(errno);
				write(2, sterr, ft_strlen(sterr));
				write(2, "\n", 1);
			}
			if (com->cmd)
			{
				dup2(fd, STDIN_FILENO);
				close(fd);
				r = cmd_caller(com, env_head, cmd_head, ret, user, envp);
			}
			exit(0);
		}
		else if (pid < 0)
		{
			sterr = strerror(errno);
			write(2, sterr, ft_strlen(sterr));
			write(2, "\n", 1);
		}
		wait(NULL);
	}
	i = 0;
	while (i < com->n_redir)
	{
		free(redir[i].type);
		free(redir[i].file);
		i++;
	}
	free(redir);
	return(0);
}
