/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:53:05 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/03 15:01:31 by ajuncosa         ###   ########.fr       */
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

void	funcion_de_pipes(t_list *lst)
{
	if (((t_cmd*)lst->content)->sep_0 == '|')
	{
		printf("redirigir entrada al comando: %s\n", ((t_cmd*)lst->content)->cmd);
	}
	if (((t_cmd*)lst->content)->sep_1 == '|')
	{
		printf("crear pipe\n");
		printf("redirigir salida y hacer comando: %s\n", ((t_cmd*)lst->content)->cmd);
		funcion_de_pipes(lst->next);
	}
	else
		printf("hacer comando: %s\n", ((t_cmd*)lst->content)->cmd);
	return ;
}

int	parser(char *str, t_list **env_head, int ret, char *user)	// TODO: meter cmd, args y sep en una lista, en lugar de imprimirlo con printfs y reemplazarlo por cada vuelta al bucle
{
	int     i;
	t_list	*cmd_head;
	t_list	*new;
	t_cmd	*com;
	t_list	*lst;
	int		r;

	i = 0;
	cmd_head = NULL;
	while (str[i] != '\n')
	{
		// ALOCAR LISTA Y CONTENT
		if (!(new = malloc(sizeof(t_list))))
		{
			ft_free_cmd(&cmd_head);
			ft_exit(env_head, user);
		}
		if (!(com = malloc(sizeof(t_cmd))))
		{
			ft_free_cmd(&cmd_head);
			ft_exit(env_head, user);
		}
		new->content = com;
		
		// INICIALIZAR COSAS
		((t_cmd*)new->content)->sep_0 = '0';
		((t_cmd*)new->content)->sep_1 = '0';
		((t_cmd*)new->content)->args = NULL;
		((t_cmd*)new->content)->cmd = NULL;

		// BUSCAR sep_0 (el separador de comandos (; o |) que viene antes del comando actual)
		if (str[i] == ';' || str[i] == '|')
		{
			if (i > 0)
				((t_cmd*)new->content)->sep_0 = str[i];
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
		if (!(((t_cmd*)new->content)->cmd = find_cmd(str, &i)))
		{
			ft_free_cmd(&cmd_head);
			ft_exit(env_head, user);
		}
		while (str[i] == ' ')
			i++;
		
		// CONTAR ARGUMENTOS Y ALOCAR ARGS
		((t_cmd*)new->content)->n_args = count_args(&str[i]);
		if (((t_cmd*)new->content)->n_args == -1)
		{
			ft_free_cmd(&cmd_head);
			return (0);
		}
		if (((t_cmd*)new->content)->n_args > 0)
			if (!(((t_cmd*)new->content)->args = malloc(((t_cmd*)new->content)->n_args * sizeof(char *))))
			{
				ft_free_cmd(&cmd_head);
				ft_exit(env_head, user);
			}

		// GUARDAR ARGUMENTOS
		if (!(save_args(str, ((t_cmd*)new->content)->n_args, ((t_cmd*)new->content)->args, &i)))
		{
			ft_free_cmd(&cmd_head);
			ft_exit(env_head, user);
		}
															//TODO: si ponen ; y | a la vez e.g. "ls ;| wc" tiene que dar error
		// GUARDAR sep_1									//TODO: si la línea acaba en | sin nada detrás se queda el pipe abierto (¿hay que tenerlo en cuenta o devolver un error como con las comillas?)
		if (str[i] == ';' || str[i] == '|')
			 ((t_cmd*)new->content)->sep_1 = str[i];
		/*if (com.sep_0 == '|' && com.sep_1 == '|')		//FIXME: por qué esta condicion???? tal vez quería gestionar || y lo he hecho mal (no es un error real pero es un bonus)
		{
			write(1, "parse error near `|'\n", 21);
			return ;
		}*/

		//GUARDAR COMANDO EN LISTA
		ft_lstadd_back(&cmd_head, new);
	}
	//PRINTFS
	/**lst = cmd_head;
	while (lst)
	{
		printf("_________________________\n");
		printf("comando: %s\n", ((t_cmd*)lst->content)->cmd);
		printf("n de args: %d\n", ((t_cmd*)lst->content)->n_args);
		i = 0;
		while (i < ((t_cmd*)lst->content)->n_args)
		{
			printf("arg[%d]: %s\n", i, ((t_cmd*)lst->content)->args[i]);
			i++;
		}
		printf("sep_0: %c, sep_1: %c\n", ((t_cmd*)lst->content)->sep_0, ((t_cmd*)lst->content)->sep_1);
		lst = lst->next;
	}*/

	// HACER COMANDOS
	lst = cmd_head;
	while (lst)
	{
		if (((t_cmd*)lst->content)->sep_0 != '|' && ((t_cmd*)lst->content)->sep_1 != '|')
		{
			if (!strncmp(((t_cmd*)lst->content)->cmd, "pwd", 4)) //TODO: hacer una función que parsee los comandos tipo el parser_old, y llamarla dentro y fuera de las condiciones anteriores (en lugar de ft_cmd)
				r = ft_pwd(((t_cmd*)lst->content)->cmd, ((t_cmd*)lst->content)->args);	//TODO: arreglar todas las funciones para adaptarlas al nuevo parseador, y hacer que los comandos de /bin/ puedan recibir los argumentos tb?
			else
				r = ft_cmd(((t_cmd*)lst->content)->cmd);
		}
		else if (((t_cmd*)lst->content)->sep_1 == '|')
		{
			funcion_de_pipes(lst);
			while (((t_cmd*)lst->content)->sep_1 == '|')
				lst = lst->next;
		}
		lst = lst->next;
	}
	
	// FREES DE ESTA LÍNEA DE COMANDOS
	ft_free_cmd(&cmd_head);
	return (r);
}



/*
// HACER COMANDO
	int		fd1[2];
	int		status;
	int		pid;
	char 	*sterr;
	pipe(fd1);
	if (com.sep_1 == '|')
	{
		pid = fork();
		if (pid == 0)
		{
			close(fd1[0]);
			dup2(fd1[1], STDOUT_FILENO);
			close(fd1[1]);
			//printf("HACER PRIMER COMANDO DEL PIPE\n");
			if (!strncmp(com.cmd, "pwd", 4))
				r = ft_pwd(com.cmd, com.args);
			else
				r = ft_cmd(com.cmd);
			exit(0);
		}
		else if (pid > 0)
		{
			close(fd1[1]);
			printf("ret wait1: %d\n", wait(&status));
		}
		else 
		{
			sterr = strerror(errno);
			write(1, sterr, ft_strlen(sterr));
			write(1, "\n", 1);
		}
	}
	if (com.sep_0 == '|')
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(fd1[0], STDIN_FILENO);
			close(fd1[0]);
			//printf("HACER SEGuNDo CoMAndO DEL PIPE\n");
			if (!strncmp(com.cmd, "pwd", 4))
				r = ft_pwd(com.cmd, com.args);
			else
				r = ft_cmd(com.cmd);
			exit(0);
		}
		else if (pid > 0)
		{
			close(fd1[0]);
			printf("ret wait2: %d\n", wait(&status));
		}
		else 
		{
			sterr = strerror(errno);
			write(1, sterr, ft_strlen(sterr));
			write(1, "\n", 1);
		}
	}
	else if (com.sep_0 != '|' && com.sep_1 != '|')
	{
		if (!strncmp(com.cmd, "pwd", 4)) //TODO: hacer una función que parsee los comandos tipo el parser_old, y llamarla dentro y fuera de las condiciones anteriores (en lugar de ft_cmd)
			r = ft_pwd(com.cmd, com.args);	//TODO: arreglar todas las funciones para adaptarlas al nuevo parseador, y hacer que los comandos de /bin/ puedan recibir los argumentos tb?
		else
			r = ft_cmd(com.cmd);
	}
*/