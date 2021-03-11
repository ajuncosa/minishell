/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 11:27:11 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/11 13:49:01 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

 /* TODO: añadir echo $var con las variables de env */

int	ft_echo(t_cmd *com)
{
	int	n;
	int	i;
	int j;
	int k;

	n = 0;
	i = 0;
	j = 0;
	while (!ft_strncmp(com->args[j], "-n", 2))
	{
		k = 1;
		while (com->args[j][k] == 'n')
			k++;
		if (com->args[j][k] == '\0')
		{
			i = j + 1;
			n = 1;
		}
		else
		{
			i = j;
			break;
		}
		j++;
	}
	while (i < com->n_args)
	{
		write(1, com->args[i], ft_strlen(com->args[i]));
		if (i < com->n_args - 1)
			write(1, " ", 1);			//FIXME: si no hay espacio entre dos argumentos de comillas, no hay que dejar espacio (el parseador tiene que mirar dónde hay espacio?) e.g. echo "hola"'adios'
		i++;
	}
	if (n == 0)
		write(1, "\n", 1);
	return (0);
}
