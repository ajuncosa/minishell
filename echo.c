/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 11:27:11 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/08 20:56:25 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

 /* TODO: añadir echo $var con las variables de env */

int	ft_echo(t_cmd *com)
{
	int	n;
	int	i;
	int	j;
	int	end;

	n = 0;
	i = 0;
	j = 0;
	/*
	while (args != NULL)
	{
		printf("args: %s\n", args[i]);
		i++;
	}
	*/
	/*
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		j = i + 1;
		while (str[j] == 'n')
		{
			j++;
			if (str[j] == ' ' || str[j] == '\n')
			{
				n = 1;
				i = j;
				if (str[j] == ' ' && str[j + 1] == '-' && str[j + 2] == 'n')
					j += 2;
			}
		}
	}
	*/
	while (i < com->n_args)
	{
		if (com->args[i][j] == '"')
		{
			j++;
			end = j;
			while (com->args[i][end] != '"' && com->args[i][end] != '\n' && com->args[i][end] != '\0')
				end++;
			if (com->args[i][end] != '"')
			{
				write(1, "Error: open dquote\n", 19);
				return (1);
			}
			write(1, &com->args[i], end - j);
			j = end + 1;
		}
		else if (com->args[i][j] == '\'')
		{
			//printf("aqui");
			j++;
			end = j;
			while (com->args[i][end] != '\'' && com->args[i][end] != '\n' && com->args[i][end] != '\0')
				end++;
			if (com->args[i][end] != '\'')
			{
				write(1, "Error: open quote\n", 18);
				return (1);
			}
			write(1, &com->args[i], end - j);
			j = end + 1;
		}
		else
		{
			end = j;													//para imprimir por palabras con un solo espacio, y teniendo en cuenta que pueden venir strings con comillas después
			while (com->args[i][end] != ' ' && com->args[i][end] != '"' && com->args[i][end] != '\'' && com->args[i][end] != '\n' && com->args[i][end] != '\0')
				end++;
			write(1, com->args[i], end - j);
			j = end;
		}
		/*
		while (str[i] == ' ')											// he movido esto al final del bucle para que solo haga lo de poner un espacio (ver siguiente comentario) cuando es entre palabras, no al principio de la primera palabra (xq encuentra el espacio de "echo ")
			i++;
		if (str[i - 1] == ' ')											// esto es para que cuando hay varias palabras separadas por uno o varios espacios, que ponga sólo uno
			write(1, " ", 1);
			*/
		i++;
	}
	if (n == 0)
		write(1, "\n", 1);
	return (0);
}
