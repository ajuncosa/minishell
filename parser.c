/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:53:05 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/02/26 11:38:01 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_cmd(char *str, int *i)
{
	int		start;
	int		end;
	char	*cmd;

	start = *i;
	while (str[start] == ' ')
		start++;
	end = start;
	while (str[end] != ' ' && str[end] != '\n' && str[end] != ';'
		&& str[end] != '|' && str[end] != '\0')
		end++;
	if (!(cmd = ft_substr(str, start, end - start)))
		return (NULL);
	*i = end;
	return (cmd);
}

int		count_args(char *str)
{
	int i;
	int	n_args;
	
	i = 0;
	n_args = 0;
	while (str[i] != '\n' && str[i] != ';' && str[i] != '|' && str[i] != '\0')
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' && str[i] != '\n' && str[i] != '\0')
				i++;
			if (str[i] != '"')
			{
				write(1, "Error: open dquote\n", 19);
				return (-1);
			}
			n_args++;
			i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i] != '\n' && str[i] != '\0')
				i++;
			if (str[i] != '\'')
			{
				write(1, "Error: open quote\n", 18);
				return (-1);
			}
			n_args++;
			i++;
		}
		else
		{	// FIXME: algunos argumentos, e.g. redirections, van a incluir espacios. Añadir condiciones aparte para esos casos
			while (str[i] != ' ' && str[i] != '"' && str[i] != '\''
				&& str[i] != '\n'  && str[i] != ';' && str[i] != '|'
				&& str[i] != '\0')
				i++;
			n_args++;
		}
		while (str[i] == ' ')
			i++;
	}
	return (n_args);
}

int		save_args(char *str, int n_args, char **args, int *start)
{
	int	end;
	int	n;

	n = 0;
	while (n < n_args)
	{
		if (str[*start] == '"')
		{
			*start += 1;
			end = *start;
			while (str[end] != '"' && str[end] != '\n' && str[end] != '\0')
				end++;
			if (!(args[n] = ft_substr(str, *start, end - *start)))
				return (0);
			*start = end + 1;
		}
		else if (str[*start] == '\'')
		{
			*start += 1;
			end = *start;
			while (str[end] != '\'' && str[end] != '\n' && str[end] != '\0')
				end++;
			if (!(args[n] = ft_substr(str, *start, end - *start)))
				return (0);
			*start = end + 1;
		}
		else
		{
			end = *start;
			// FIXME: algunos argumentos, e.g. redirections, van a incluir espacios. Añadir condiciones aparte para esos casos
			while (str[end] != ' ' && str[end] != '"' && str[end] != '\''
				&& str[end] != '\n'  && str[end] != ';' && str[end] != '|'
				&& str[end] != '\0')
				end++;
			if (!(args[n] = ft_substr(str, *start, end - *start)))
				return (0);
			*start = end;
		}
		while (str[*start] == ' ')
			*start += 1;
		n++;
	}
	return (1);
}

int	parser(char *str, t_list **head, int ret, char *user)	// TODO: meter cmd, args y sep en una lista, en lugar de imprimirlo con printfs y reemplazarlo por cada vuelta al bucle
{
	int     i;
	int		j;
	t_cmd	com;
	int		n;
	int		n_args;
	int		r;

	i = 0;
	while (str[i] != '\n')
	{
		// INICIALIZAR COSAS
		com.sep[0] = '0';
		com.sep[1] = '0';
		com.args = NULL;
		com.cmd = NULL;

		// BUSCAR SEP[0] (el separador de comandos (; o |) que viene antes del comando actual)
		if (str[i] == ';' || str[i] == '|')
		{
			if (i > 0)
				com.sep[0] = str[i];
			else if (i == 0 && str[i] == '|')
			{
				write(1, "parse error near `|'\n", 21);
				return (2);									//FIXME: estos valores de retorno están mal
			}
			i++;
			if (str[i] == ';' && str[i - 1] == ';')
			{
				write(1, "parse error near `;;'\n", 22);
				return (130);								//FIXME: valores de retorno mal
			}
		}

		// GUARDAR COMANDO
		if (!(com.cmd = find_cmd(str, &i)))
			ft_exit(head, user);
		while (str[i] == ' ')
			i++;
		
		// CONTAR ARGUMENTOS Y ALOCAR ARGS
		n_args = count_args(&str[i]);
		if (n_args == -1)
			return (0);
		if (n_args > 0)
			if (!(com.args = malloc(n_args * sizeof(char *))))
				ft_exit(head, user);

		// GUARDAR ARGUMENTOS
		if (!(save_args(str, n_args, com.args, &i)))
			ft_exit(head, user);
															//TODO: si ponen ; y | a la vez e.g. "ls ;| wc" tiene que dar error
		// GUARDAR SEP[1]									//TODO: si la línea acaba en | sin nada detrás se queda el pipe abierto (¿hay que tenerlo en cuenta o devolver un error como con las comillas?)
		if (str[i] == ';' || str[i] == '|')
			com.sep[1] = str[i];
		/*if (com.sep[0] == '|' && com.sep[1] == '|')		//FIXME: por qué esta condicion???? tal vez quería gestionar || y lo he hecho mal (no es un error real pero es un bonus)
		{
			write(1, "parse error near `|'\n", 21);
			return ;
		}*/
		
		// PRINTFS
		/*printf("_________________________\n");
		printf("comando:   %s\n", com.cmd);
		printf("n de args: %d\n", n_args);
		j = 0;
		while (j < n_args)
		{
			printf("%s\n", com.args[j]);
			j++;
		}
		printf("sep[0]: %c, sep[1]: %c\n", com.sep[0], com.sep[1]);*/

		// HACER COMANDO
		if (!strncmp(com.cmd, "pwd", 4))
			r = ft_pwd(com.cmd, com.args);
		else
			r = ft_cmd(com.cmd);

		//FREES
		free(com.cmd);
		j = 0;
		while (j < n_args)
		{
			free(com.args[j]);
			j++;
		}
		free(com.args);
	}
	return (r);
}
