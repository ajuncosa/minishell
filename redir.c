/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:57:40 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/03/11 13:57:34 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**arg_cleaner(t_cmd *com, t_redir **redir) //FIXME: hacer frees de redir, y del contenido de cada uno
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
		if (!ft_strncmp(com->args[i], ">", ft_strlen(com->args[i])) 
		|| !ft_strncmp(com->args[i], ">>", ft_strlen(com->args[i])) 
		|| !ft_strncmp(com->args[i], "<", ft_strlen(com->args[i])))
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
		if (!ft_strncmp(com->args[i], ">", ft_strlen(com->args[i])) 
		|| !ft_strncmp(com->args[i], ">>", ft_strlen(com->args[i])) 
		|| !ft_strncmp(com->args[i], "<", ft_strlen(com->args[i])))
		{
			(*redir[k]).type = ft_strdup(com->args[i]);
			if (!(*redir[k]).type)
				return (NULL);            
			(*redir[k]).file = ft_strdup(com->args[i + 1]);
			if (!(*redir[k]).file)
				return (NULL);
			free(com->args[i]);
			free(com->args[i + 1]);
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
	com->n_args = com->n_args - n_del;
	return(new);
}

int redir_manager(t_cmd *com, t_list **env_head, int ret, char *user)
{
	char	**new;
	int		i;
	t_redir	*redir;
	int     fd;
	int     pid;
	int		r;
	char 	*sterr;

	new = arg_cleaner(com, &redir);
	/*
	i = 0;
	while(i < com->n_redir)
	{
		printf("%s, %s\n", redir[i].type, redir[i].file);
		i++;
	}
	*/
	free(com->args);
	com->args = new;
	i = 0;
	while (i < com->n_redir)
	{
		if (!ft_strncmp(redir[i].type, ">", ft_strlen(redir[i].type)))
		{
			pid = fork();
			if (pid == 0)
			{
				fd = open(redir[i].file, O_WRONLY |  O_TRUNC | O_CREAT, 0777);
				if (fd == -1)
				{
					sterr = strerror(errno);
					write(1, sterr, ft_strlen(sterr));
					write(1, "\n", 1);
				}
				dup2(fd, STDOUT_FILENO);
				close(fd);
				r = cmd_caller(com, env_head, ret, user);
				exit(0);
			}
			else if (pid < 0)
			{
				sterr = strerror(errno);
				write(1, sterr, ft_strlen(sterr));
				write(1, "\n", 1);
			}
			wait(NULL);
		}
		else if (!ft_strncmp(redir[i].type, ">>", 2))
		{
			pid = fork();
			if (pid == 0)
			{
				fd = open(redir[i].file, O_WRONLY |  O_APPEND | O_CREAT, 0777);
				if (fd == -1)
				{
					sterr = strerror(errno);
					write(1, sterr, ft_strlen(sterr));
					write(1, "\n", 1);
				}
				dup2(fd, STDOUT_FILENO);
				close(fd);
				r = cmd_caller(com, env_head, ret, user);
				exit(0);
			}
			else if (pid < 0)
			{
				sterr = strerror(errno);
				write(1, sterr, ft_strlen(sterr));
				write(1, "\n", 1);
			}
			wait(NULL);
		}
		else if (!ft_strncmp(redir[i].type, "<", 1))
		{
			pid = fork();
			if (pid == 0)
			{
				fd = open(redir[i].file, O_RDONLY);
				if (fd == -1)
				{
					sterr = strerror(errno);
					write(1, sterr, ft_strlen(sterr));
					write(1, "\n", 1);
				}
				dup2(fd, STDIN_FILENO);
				close(fd);
				r = cmd_caller(com, env_head, ret, user);
				exit(0);
			}
			else if (pid < 0)
			{
				sterr = strerror(errno);
				write(1, sterr, ft_strlen(sterr));
				write(1, "\n", 1);
			}
			wait(NULL);
		}
		i++;
	}
	return(0);
}
