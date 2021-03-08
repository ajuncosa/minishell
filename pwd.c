/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 12:51:16 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/08 11:36:46 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args)
{
	char	*pwd;
	char	*buf;
	pid_t	status;

	if (args != NULL)
	{
		write(1, "pwd: too many arguments\n", 24);
		return (1);
	}
	buf = NULL;
	buf = getcwd(buf, 0);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	free(buf);
	return (0);
}
