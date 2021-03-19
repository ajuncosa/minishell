/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 11:34:27 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/03/19 18:37:31 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pathfinder(char *cmd, t_list **env_head)
{
	t_list		*lst;
	char		**paths;
	char		*joined;
	char		*tmp;
	int			i;
	struct stat	stat;

	lst = *env_head;
	while (lst)
	{
		if (!ft_strncmp(((t_env*)lst->content)->id, "PATH", 4))
		{
			paths = ft_split(((t_env*)lst->content)->value, ':');
			break;
		}
		lst = lst->next;
	}
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		joined = ft_strjoin(tmp, cmd);
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
	return (NULL);
}

int	ft_cmd(t_cmd *com, t_list **env_head, char **envp)
{
	int 	i;
	int		j;
	t_list	*lst;
	pid_t	pid;
	char	*path;
	char	**argv;
	char	*sterr;

	// ALOCAR NUEVO ARRAY DE ARGUMENTOS PARA PASAR A EXECVE
	argv = malloc((com->n_args + 2) * sizeof(char *));			//FIXME: gestionar error
	argv[0] = ft_strdup(com->cmd);
	i = 1;
	j = 0;
	while (j < com->n_args)
	{
		argv[i] = ft_strdup(com->args[j]);
		i++;
		j++;
	}
	argv[i] = NULL;

	//BUSCAR CMD EN PATH (si no tiene formato de path con alguna '/')
	if (!ft_strchr(com->cmd, '/'))
	{
		path = ft_pathfinder(com->cmd, env_head);
		if (path == NULL)
		{
			printf("command not found\n");
			i = 0;
			while (argv[i])
			{
				free(argv[i]);
				i++;
			}
			free(argv);
			return (127);
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
			sterr = strerror(errno);
			write(2, sterr, ft_strlen(sterr));
			write(2, "\n", 1);
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
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
	return (127); //FIXME: no sabemos que retorna
}