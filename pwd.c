/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 12:51:16 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/01/29 11:40:38 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char *str)
{
	char	*pwd;
	int		i;
	char	*buf;
	pid_t	status;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] != '\n')
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
