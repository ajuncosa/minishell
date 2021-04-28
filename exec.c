/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 11:34:27 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/04/28 18:10:59 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmd(t_cmd *com, char **envp, t_data *data)
{
	int 	i;
	int		j;
	t_list	*lst;
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
		argv[i] = ft_strdup(com->args_str[j]);
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
	g_pid = fork();
	if (g_pid == 0)
	{
		if (execve(com->cmd, argv, envp) == -1)
		{
			dup2(data->std_out, STDOUT_FILENO);
			sterr = strerror(errno);
			error_msn(com->cmd, NULL, sterr);
		}
		exit(127);
	}
	else if (g_pid < 0)
	{
		sterr = strerror(errno);
		error_msn(NULL, NULL, sterr);
	}
	waitpid(g_pid, &status, 0);
	data->ret = WEXITSTATUS(status);
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}