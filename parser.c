/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:53:05 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/04/28 15:48:14 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_errors(t_letter *str)
{
	int		i;
	int		check;
	char	flag;

	i = 0;
	flag = 0;
	while (str[i].c == ' ' && !str[i].esc)
		i++;
	if ((str[i].c == ';' || str[i].c == '|') && !str[i].esc)
	{
		printf("syntax error near unexpected token `%c\'\n", str[i].c);
		return (0);
	}
	while(str[i].c != '\0')
	{
		if ((str[i].c == ';' || str[i].c == '|') && !str[i].esc)
		{
			if (flag)
			{
				printf("syntax error near unexpected token `%c\'\n", str[i].c);
				return (0);
			}
			if (str[i].c == ';')
				flag = ';';
			else if (str[i].c == '|')
				flag = '|';
			i++;
		}
		else if ((str[i].c == '>' || str[i].c == '<') && !str[i].esc)
		{
			if (flag)
			{
				printf("syntax error near unexpected token `%c\'\n", str[i].c);
				return (0);
			}
			flag = 'r';
			check = i;
			if (str[i].c == '>')
			{
				while(str[i].c == '>' && !str[i].esc && (i - check) < 2)
					i++;
			}
			else if (str[i].c == '<')
			{
				while(str[i].c == '<' && !str[i].esc && (i - check) < 1)
					i++;
			}
			if ((str[i].c == '>' || str[i].c == '<') && !str[i].esc)
			{
				printf("syntax error near unexpected token `%c\'\n", str[i - 1].c);
				return (0);
			}
		}
		else
		{
			flag = 0;
			while (!is_space_redir_or_endofcmd(str[i]))
				i++;
		}
		while (str[i].c == ' ' && !str[i].esc)
			i++;
	}
	if (flag == '|')
	{
		printf("Error: open pipe\n");
		return (0);
	}
	if (flag == 'r')
	{
		printf("syntax error near unexpected token `newline\'\n");
		return (0);
	}
	return (1);
}

void	parser(t_data *data, char *str, char **envp)
{
					//TODO: añadir parse errors de >>> <<< ><>< y eso
					//FIXME: echo hola ; $aaa | echo hola => tiene que hacer los dos comandos aunque el del medio esté vacío, no dar syntax error
	int   		i;
	int			len;
	t_list		*new;
	t_cmd		*com;

	i = 0;
	com = NULL;
	data->cmd_head = NULL;
	len = esc_size(str);
	if (len == -1)
	{
		data->ret = 0;
		return ;
	}
	data->line = line_to_struct(str, len);
	if (!data->line)
		ft_exit(data, com);
	dollar_finder(&data->env_head, &data->line, data->ret);
	if (!syntax_errors(data->line))
	{
		free(data->line);
		data->ret = 258;
		return ;
	}
	while (data->line[i].c != '\0')
	{
		// ALOCAR LISTA Y CONTENT
		if (!(new = malloc(sizeof(t_list))))
			ft_exit(data, com);
		if (!(com = malloc(sizeof(t_cmd))))
			ft_exit(data, com);
		new->content = com;

		// INICIALIZAR COSAS
		com->sep_0 = '0';
		com->sep_1 = '0';
		com->args = NULL;
		com->args_str = NULL;
		com->cmd = NULL;
	
		while (data->line[i].c == ' ' && !data->line[i].esc)
			i++;

		// BUSCAR sep_0 (el separador de comandos (; o |) que viene antes del comando actual)
		if ((data->line[i].c == ';' || data->line[i].c == '|') && !data->line[i].esc)
		{
			com->sep_0 = data->line[i].c;
			i++;
			while (data->line[i].c == ' ' && !data->line[i].esc)
				i++;
		}

		// CONTAR ARGUMENTOS Y ALOCAR ARGS
		com->n_args = count_args(&data->line[i]);
		if (com->n_args == -1)
		{
			free(new);
			free(com);
			free(data->line);
			ft_lstclear(&data->cmd_head, &del_lst_cmd);
			data->ret = 258;
			return ;
		}
		//printf("n_args: %d\n", (com)->n_args);
		else if (com->n_args == 0)
		{
			free(new);
			free(com);
			continue;
		}
		else if (com->n_args > 0)
		{
			if (!(com->args = malloc(com->n_args * sizeof(t_letter *))))
				ft_exit(data, com);
		}

		// GUARDAR ARGUMENTOS
		if (!(save_args(&data->line, com, &i)))
			ft_exit(data, com);

		// BUSCAR COMANDO Y GUARDAR POR SEPARADO
		if (!find_cmd(com))
			ft_exit(data, com);

		// GUARDAR sep_1
		if ((data->line[i].c == ';' || data->line[i].c == '|') && !data->line[i].esc)
			 (com)->sep_1 = data->line[i].c;

		//GUARDAR COMANDO EN LISTA
		ft_lstadd_back(&data->cmd_head, new);
	}

	//HACER  COMANDOS
	cmd_manager(data, envp);
	
	//REINICIAR PID PARA PODER HACER CTRL-C CUANDO UN PROCESO DEJE LA PID CAMBIADA AL TERMINAR
	pid = -1;

	// FREES DE ESTA LÍNEA DE COMANDOS
	free(data->line);
	data->line = NULL;
	ft_lstclear(&data->cmd_head, &del_lst_cmd);
}
