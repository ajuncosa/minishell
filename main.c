/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:36:03 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/12/15 13:34:22 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char *str)
{
	int	n;
	int	i;
	int	end_quote;

	n = 0;
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' && str[i + 1] == 'n' && (str[i + 2] == ' ' || str[i + 2] == '\n'))
	{
		n = 1;
		i += 2;
	}
	while (str[i] != '\n')
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '"')
		{
			i++;
			end_quote = i;
			while (str[end_quote] != '"' && str[end_quote] != '\n')
				end_quote++;
			if (str[end_quote] != '"')
				write(1, "COMILLA ABIERTA\n", 16);						// fix: qué pasa si se queda la comilla abierta!?
			write(1, &str[i], end_quote - i);
			i = end_quote + 1;
		}
		else if (str[i] == '\'')
		{
			i++;
			end_quote = i;
			while (str[end_quote] != '\'' && str[end_quote] != '\n')
				end_quote++;
			if (str[end_quote] != '\'')
				write(1, "COMILLA ABIERTA\n", 16);
			write(1, &str[i], end_quote - i);
			i = end_quote + 1;
		}
		else
			write(1, &str[i], ft_strlen(&str[i]) - 1);
	}
	if (n == 0)
		write(1, "\n", 1);
}

int		main(int argc, char **argv, char **envp)
{
	int		i;
	char	str[1024];
	char	*path;
	char	*user_line;
	char	*user;
	size_t	user_len;

	printf("\033[1;36m                                         _       _       \n              _                         (_)     (_)      \n ____   ___ _| |_     ___  ___     ____  _ ____  _       \n|  _ \\ / _ (_   _)   /___)/ _ \\   |    \\| |  _ \\| |      \n| | | | |_| || |_   |___ | |_| |  | | | | | | | | |  _ _ _ \n|_| |_|\\___/  \\__)  (___/ \\___/   |_|_|_|_|_| |_|_| (_|_|_)\033[0m\n\n");


	path = NULL;
	user = NULL;
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			path = ft_strdup(envp[i]);
		else if(!ft_strncmp(envp[i], "USER=", 5))
			user_line = ft_strdup(envp[i]);
		i++;
	}
	user = ft_strtrim(user_line, "USER=");
	free(user_line);
	user_len = ft_strlen(user);
	while (1)
	{
		write(1, user, user_len);
		write(1, "> ", 2);
		read(0, str, 1023);
		if (!ft_strncmp(str, "echo ", 5))
			echo(&str[5]);
		if (!ft_strncmp(str, "exit", 4)) 				// to do: check if line is empty after command :D
			exit(0);
		ft_bzero(str, 1023);
	}

	return (0);
}
