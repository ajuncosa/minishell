/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 11:34:27 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/02/16 13:37:44 by cruiz-de         ###   ########.fr       */
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

int	ft_cmd(char *str)
{
	int i;
	int	argc;
	char *sterr;
	char **argv;
	char *envp[] = {NULL};

	argv = ft_split(str, ' ');
	argc = 0;
	while (argv[argc] != NULL)
		argc++;
	ft_chomp(argv[argc - 1]);

	if (execve(argv[0], argv, envp) == -1)
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
	write(1, "command not found\n", 18);								// possible TODO: replicar mensaje
	return (127);
}