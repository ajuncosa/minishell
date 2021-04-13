/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 11:34:27 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/04/13 15:54:54 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pathfinder(char *cmd, t_data *data)
{
	t_list		*lst;
	char		**paths;
	char		*joined;
	char		*tmp;
	int			i;
	struct stat	stat;
	
	lst = data->env_head;
	paths = NULL;
	while (lst)
	{
		if (!ft_strcmp(((t_env*)lst->content)->id, "PATH"))
		{
			if (((t_env*)lst->content)->value)
			{
				paths = ft_split(((t_env*)lst->content)->value, ':');
				if (!paths)
					ft_exit(data, NULL);
			}
			break;
		}
		lst = lst->next;
	}
	if (paths)
	{
		i = 0;
		while (paths[i])
		{
			tmp = ft_strjoin(paths[i], "/");
			if (!tmp)
				ft_exit(data, NULL);
			joined = ft_strjoin(tmp, cmd);
			if (!joined)
				ft_exit(data, NULL);
			free(tmp);
			lstat(joined, &stat);
			if (S_ISREG(stat.st_mode))
			{
				i = 0;
				while (paths[i])
				{
					free(paths[i]);
					i++;
				}
				free(paths);
				return (joined);
			}
			free(joined);
			i++;
		}
		i = 0;
		while (paths[i])
		{
			free(paths[i]);
			i++;
		}
		free(paths);
	}
	return (NULL);
}

void	ft_cmd(t_cmd *com, char **envp, t_data *data)
{
	int 	i;
	int		j;
	t_list	*lst;
	//pid_t	pid;
	char	*path;
	char	**argv;
	char	*sterr;
	int		status;

	// ALOCAR NUEVO ARRAY DE ARGUMENTOS PARA PASAR A EXECVE
	argv = malloc((com->n_args + 2) * sizeof(char *));
	if (!argv)
		ft_exit(data, com);
	argv[0] = ft_strdup(com->cmd);
	if (!argv[0])
		ft_exit(data, com);
	i = 1;
	j = 0;
	while (j < com->n_args)
	{
		argv[i] = ft_strdup(com->args[j]);
		if (!argv[i])
			ft_exit(data, com);
		i++;
		j++;
	}
	argv[i] = NULL;

	//BUSCAR CMD EN PATH (si no tiene formato de path con alguna '/')
	if (!ft_strchr(com->cmd, '/'))
	{
		path = ft_pathfinder(com->cmd, data);
		if (path == NULL)
		{
			dup2(data->std_out, STDOUT_FILENO);
			error_msn(com->cmd, NULL, "command not found");
			i = 0;
			while (argv[i])
			{
				free(argv[i]);
				i++;
			}
			free(argv);
			data->ret = 127;
			return ;
		}
		free(com->cmd);
		com->cmd = path;
	}

	//EJECUTAR CON EXECVE
	pid = fork();
	if (pid == 0)
	{
		if (execve(com->cmd, argv, envp) == -1)
		{
			dup2(data->std_out, STDOUT_FILENO);
			sterr = strerror(errno);
			error_msn(com->cmd, NULL, sterr);
		}
		exit(127);
	}
	else if (pid < 0)
	{
		sterr = strerror(errno);
		error_msn(NULL, NULL, sterr);
	}
	wait(&status);
	data->ret = WEXITSTATUS(status);
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}