/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 11:27:11 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/12/22 14:02:27 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char *str)
{
	int	n;
	int	i;
	int	j;
	int	end;

	n = 0;
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		j = i + 1;
		while (str[j] == 'n')											// FIXME: falta por arreglar caso echo -nn -n-n
		{
			j++;
			if (str[j] == ' ' && str[j + 1] == '-' && str[j + 2] == 'n')
			{
				n = 1;
				i = j;
				j += 2;

			}
		}
		if (str[j] == ' ' || str[j] == '\n')
		{
			n = 1;
			i = j;
		}
	}

	while (str[i] == ' ')												// para saltarse los espacios extra después de echo o después de -n
		i++;
	while (str[i] != '\n')
	{
		if (str[i] == '"')
		{
			i++;
			end = i;
			while (str[end] != '"' && str[end] != '\n' && str[end] != '\0')
				end++;
			if (str[end] != '"')
			{
				write(1, "Error: open dquote\n", 19);
				return ;
			}
			write(1, &str[i], end - i);
			i = end + 1;
		}
		else if (str[i] == '\'')
		{
			i++;
			end = i;
			while (str[end] != '\'' && str[end] != '\n' && str[end] != '\0')
				end++;
			if (str[end] != '\'')
			{
				write(1, "Error: open quote\n", 18);
				return ;
			}
			write(1, &str[i], end - i);
			i = end + 1;
		}
		else
		{
			end = i;													//para imprimir por palabras con un solo espacio, y teniendo en cuenta que pueden venir strings con comillas después
			while (str[end] != ' ' && str[end] != '"' && str[end] != '\'' && str[end] != '\n' && str[end] != '\0')
				end++;
			write(1, &str[i], end - i);
			i = end;
		}
		while (str[i] == ' ')											// he movido esto al final del bucle para que solo haga lo de poner un espacio (ver siguiente comentario) cuando es entre palabras, no al principio de la primera palabra (xq encuentra el espacio de "echo ")
			i++;
		if (str[i - 1] == ' ')											// esto es para que cuando hay varias palabras separadas por uno o varios espacios, que ponga sólo uno
			write(1, " ", 1);
	}
	if (n == 0)
		write(1, "\n", 1);
}
