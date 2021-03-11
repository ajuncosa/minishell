/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 11:34:27 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/03/11 15:15:32 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_chomp(char *str)
{
	int i;

	i = ft_strlen(str);
	if (str[i - 1] == '\n')
		str[i - 1] = '\0';
}

int	ft_cmd(t_cmd *com)
{
	int i;
	int	j;
	pid_t pid;
	char *sterr;
	char **argv;
	char *envp[] = {NULL};					//FIXME: norminette acepta esto?

	argv = malloc((com->n_args + 1) * sizeof(char *));
	argv[0] = ft_strdup(com->cmd);
	i = 1;
	j = 0;
	while (j < com->n_args)
	{
		argv[i] = ft_strdup(com->args[j]);
		i++;
		j++;
	}
	/*i = 0;
	while (argv[i])
	{
		printf("%s\n", argv[i]);
		i++;
	}*/
	pid = fork();
	if (pid == 0)
	{
		if (execve(com->cmd, argv, envp) == -1) //FIXME: da segmentation fault al poner /bin/echo hola
		{
			sterr = strerror(errno);
			write(1, sterr, ft_strlen(sterr));
			write(1, "\n", 1);
		}
	}
	else if (pid > 0)
		wait(NULL);
	else 
	{
		sterr = strerror(errno);
		write(1, sterr, ft_strlen(sterr));
		write(1, "\n", 1);
	}
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
	write(1, "command not found\n", 18);	// posible TODO: replicar mensaje, FIXME: que solo diga esto cuando no encuentra el comando!!
	return (127);
}