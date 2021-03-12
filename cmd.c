/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 11:34:27 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/03/12 13:30:30 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd(t_cmd *com)
{
	int i;
	int	j;
	pid_t pid;
	char *sterr;
	char **argv;
	char *envp[] = {NULL};					//FIXME: norminette acepta esto?

	argv = malloc((com->n_args + 2) * sizeof(char *));
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
	pid = fork();
	if (pid == 0)
	{
		if (execve(com->cmd, argv, envp) == -1)
		{
			sterr = strerror(errno);
			write(1, sterr, ft_strlen(sterr));
			write(1, "\n", 1);
		}
		exit(0);
	}
	else if (pid < 0)
	{
		sterr = strerror(errno);
		write(1, sterr, ft_strlen(sterr));
		write(1, "\n", 1);
	}
	wait(NULL);
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
	//write(1, "command not found\n", 18);
	return (127);
}