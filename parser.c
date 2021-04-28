/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:53:05 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/04/28 12:10:16 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_data *data, char *str, char **envp)
{					//FIXME: syntax error si viene un | > sin nada entre medias
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
	
		while (data->line[i].c == ' ')
			i++;

		// BUSCAR sep_0 (el separador de comandos (; o |) que viene antes del comando actual)
		if ((data->line[i].c == ';' || data->line[i].c == '|') && !data->line[i].esc)
		{
			if (!data->cmd_head)
			{
				printf("syntax error near unexpected token `%c\'\n", data->line[i].c);
				free(new);
				free(com);
				free(data->line);
				data->ret = 258;
				return ;
			}
			else
				com->sep_0 = data->line[i].c;
			i++;
			while (data->line[i].c == ' ')
				i++;
			if ((data->line[i].c == ';' || data->line[i].c == '|') && !data->line[i].esc)
			{
				printf("syntax error near unexpected token `%c\'\n", data->line[i].c);
				free(new);
				free(com);
				free(data->line);
				ft_lstclear(&data->cmd_head, &del_lst_cmd);
				data->ret = 258;
				return ;
			}
			if (com->sep_0 == '|' && data->line[i].c == '\0')
			{
				printf("Error: open pipe\n");
				free(new);
				free(com);
				free(data->line);
				ft_lstclear(&data->cmd_head, &del_lst_cmd);
				data->ret = 258;
				return ;
			}
		}

		// CONTAR ARGUMENTOS Y ALOCAR ARGS
		com->n_args = count_args(&data->line[i]);
		if (com->n_args == -1) //FIXME:Esto solo se da si count_args tiene un parsing error
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

	/*t_list *lst = data->cmd_head;
	while (lst)
	{
		int j = 0;
			printf("cmd: %s\n", ((t_cmd*)lst->content)->cmd);
		int k = 0;
		while (k < ((t_cmd*)lst->content)->n_args)
		{
			j = 0;
			printf("arg %d\n", k);
			while (((t_cmd*)lst->content)->args[k][j].c != '\0')
			{
				printf("str: %c esc: %d\n", ((t_cmd*)lst->content)->args[k][j].c, ((t_cmd*)lst->content)->args[k][j].esc);
				j++;
			}
			k++;
		}
		lst = lst->next;
	}*/


	//HACER  COMANDOS
	cmd_manager(data, envp);
	
	//REINICIAR PID PARA PODER HACER CTRL-C CUANDO UN PROCESO DEJE LA PID CAMBIADA AL TERMINAR
	pid = -1;

	// FREES DE ESTA LÍNEA DE COMANDOS
	free(data->line);
	data->line = NULL;
	ft_lstclear(&data->cmd_head, &del_lst_cmd);
}
