/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:49:48 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/01/25 13:34:30 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_cd(char *str)							/* TODO: cd sin nada después */
{   
	char	*trimmed;
	int 	i;
	char	*sterr;

	i = 0;
	while (str[i] == ' ')
		i++;
	trimmed = ft_strtrim(&str[i], " \n");
	if (chdir(trimmed) == -1)
	{
		sterr = strerror(errno);
		write(1, sterr, ft_strlen(sterr));
		write(1, "\n", 1);
	}
}
