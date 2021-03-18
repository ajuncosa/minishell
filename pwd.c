/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 12:51:16 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/18 18:25:39 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args)
{
	char	*pwd;
	char	*buf;

	if (args != NULL)
	{
		write(1, "pwd: too many arguments\n", 24);
		return (1);
	}
	buf = NULL;
	buf = getcwd(buf, 0);
	printf("%s\n", buf);
	free(buf);
	return (0);
}
