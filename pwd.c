/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 12:51:16 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/01/25 12:51:46 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char *str)
{
	char	*pwd;
	int		i;
	char	*buf;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] != '\n')
	{
		write(1, "pwd: too many arguments\n", 24);
		return ;
	}
	buf = NULL;
	buf = getcwd(buf, 0);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	free(buf);
}
