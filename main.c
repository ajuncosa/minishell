/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:36:03 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/12/14 13:08:51 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		i;
	char	str[1000];
	char	*path;
	char	*user_line;
	char	*user;
	size_t	user_len;

	path = NULL;
	user = NULL;
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))		// to do: take env variables :D
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
		read(0, str, 999);
		if (!ft_strncmp(str, "exit", 4)) 				// to do: empty line after command :D
			exit(0);
	}
	free(path);
	free(user);
	return (0);
}
