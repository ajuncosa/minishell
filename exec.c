/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 11:34:27 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/04/30 18:52:18 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**alloc_arg_array(t_data *data, t_cmd *com)
{
	char	**argv;
	int		i;
	int		j;

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
	return (argv);
}

void	exec_cmd(t_data *data, t_cmd *com, char **argv)
{
	char	*sterr;
	int		status;

	g_pid = fork();
	if (g_pid == 0)
	{
		if (execve(com->cmd, argv, data->envp) == -1)
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
}

void	ft_cmd(t_cmd *com, t_data *data)
{
	char	*path;
	char	**argv;

	argv = alloc_arg_array(data, com);
	if (!ft_strchr(com->cmd, '/'))
	{
		path = ft_pathfinder(com->cmd, data);
		if (path == NULL)
		{
			dup2(data->std_out, STDOUT_FILENO);
			error_msn(com->cmd, NULL, "command not found");
			free_str_array(argv);
			data->ret = 127;
			return ;
		}
		free(com->cmd);
		com->cmd = path;
	}
	exec_cmd(data, com, argv);
	free_str_array(argv);
}
