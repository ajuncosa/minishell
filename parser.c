/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:53:05 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/04/26 13:15:01 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_cmd(t_cmd *com)
{
	int			i;
	int			j;
	int			n;
	int			found;
	char 		*arg;
	t_letter	**tmp;

	n = 0;
	found = 0;
	while (n < com->n_args)
	{
		arg = struct_to_str(com->args[n], 0, esc_strlen(com->args[n]));
		if (strcmp(arg, ">") && strcmp(arg, "<") && strcmp(arg, ">>"))
		{
			com->cmd = arg;
			if (!com->cmd)
				return (0);
			free(com->args[n]);
			found = 1;
			break;
		}
		free(arg);
		n += 2;
	}
	if (found)
		tmp = malloc((com->n_args - 1) * sizeof(t_letter *));
	else
		tmp = malloc(com->n_args * sizeof(t_letter *));
	if (!tmp)
		return (0);
	i = 0;
	j = 0;
	while (i < com->n_args)
	{
		if (found && i == n)
		{
			i++;
			continue;
		}
		tmp[j] = esc_dup(com->args[i]);
		if (!tmp[j])
			return (0);
		free(com->args[i]);
		j++;
		i++;
	}
	free(com->args);
	com->args = tmp;
	if (found)
	{
		com->n_args -= 1;
		if (com->n_args == 0)
		{
			free(com->args);
			com->args = NULL;
		}
	}
	return (1);
}

int		count_args(t_letter *str)
{
	int i;
	int	n_args;
	int	redir;

	redir = 0;
	i = 0;
	n_args = 0;
	while (str[i].c != '\0')
	{
		if ((str[i].c == ';' || str[i].c == '|') && !str[i].esc)
		{
			if (redir)
			{
				printf("syntax error near unexpected token `%c\'\n", str[i].c);
				return (-1);
			}
			break ;
		}
		if ((str[i].c == '>' || str[i].c == '<') && !str[i].esc)	//TODO: GESTIONAR AQUI LOS SYNTAX ERRORS?
		{
			if (redir)
			{
				printf("syntax error near unexpected token `%c\'\n", str[i].c);
				return (-1);
			}
			n_args++;
			while((str[i].c == '>' || str[i].c == '<') && !str[i].esc)
				i++;
			redir = 1;
		}
		else
		{
			while (!is_space_redir_or_endofcmd(str[i]))
				i++;
			n_args++;
			redir = 0;
		}
		while (str[i].c == ' ' && !str[i].esc)
			i++;
	}
	if (redir)
	{
		printf("syntax error near unexpected token `newline\'\n");
		return (-1);
	}
	return (n_args);
}

int		save_args(t_letter **str, t_cmd *com, int *start)
{
	int			end;
	int			n;
	t_letter	*tmp;
	
	tmp = quote_hunter(*str);
	if (!tmp)
		return (0);
	free(*str);
	*str = tmp;
	/*int i = 0;
	while (i < esc_strlen(*str))
	{
		printf("str: %c esc: %d\n", (*str)[i].c, (*str)[i].esc);
		i++;
	}*/
	while ((*str)[*start].c == ' ' && !(*str)[*start].esc)
		*start += 1;
	n = 0;
	while (n < com->n_args)
	{
		end = *start;
		if (((*str)[*start].c == '>' || (*str)[*start].c == '<') && !(*str)[*start].esc)
		{
			while (((*str)[end].c == '>' || (*str)[end].c == '<') && !(*str)[end].esc)
				end++;
		}
		else
		{
			while (!is_space_redir_or_endofcmd((*str)[end]))
				end++;
		}
		com->args[n] = esc_substr(*str, *start, end - *start);
		if (!com->args[n])
			return (0);
		*start = end;
		while ((*str)[*start].c == ' ' && !(*str)[*start].esc)
			*start += 1;
		n++;
	}
	return (1);
}

void	cmd_caller(t_cmd *com, t_data *data, char **envp)
{
	int len;

	len = ft_strlen(com->cmd);
	if (!ft_strcmp(com->cmd, "echo"))
		ft_echo(data, com);
	else if (!ft_strcmp(com->cmd, "pwd"))
		ft_pwd(data, com->args_str);
	else if (!ft_strcmp(com->cmd, "export"))
		ft_export(data, com);
	else if (!ft_strcmp(com->cmd, "cd"))
		ft_cd(data, com);
	else if (!ft_strcmp(com->cmd, "unset"))
		ft_unset(data, com);
	else if (!ft_strcmp(com->cmd, "env"))
		ft_env(data, com->args_str);
	else if (!ft_strcmp(com->cmd, "exit"))
		ft_exit(data, com);
	else
		ft_cmd(com, envp, data);
}

void	cmd_manager(t_data *data, char **envp)
{
	int		fd[2];
	int		fd_read;
	t_list	*lst;
	char	*sterr;
	int		status;

	lst = data->cmd_head;
	fd_read = 0;
	while (lst)
	{
		if (((t_cmd*)lst->content)->sep_0 != '|' && ((t_cmd*)lst->content)->sep_1 != '|')
		{
			if (check_if_redir(((t_cmd*)lst->content)))
				redir_manager(((t_cmd*)lst->content), data, envp);
			else
			{
				if (!create_args_str((t_cmd*)lst->content))
					ft_exit(data, (t_cmd*)lst->content);
				cmd_caller(((t_cmd*)lst->content), data, envp);
			}
		}
		if (((t_cmd*)lst->content)->sep_1 == '|')
		{
			pipe(fd);
			pid = fork();
			if (pid == 0)
			{
				if (fd_read)
				{
					dup2(fd_read, STDIN_FILENO);
					close(fd_read);
				}
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				if (check_if_redir(((t_cmd*)lst->content)))
					redir_manager(((t_cmd*)lst->content), data, envp);
				else
				{
					if (!create_args_str((t_cmd*)lst->content))
						ft_exit(data, (t_cmd*)lst->content);
					cmd_caller(((t_cmd*)lst->content), data, envp);
				}
				exit(data->ret);
			}
			else if (pid < 0)
			{
				sterr = strerror(errno);
				error_msn(NULL, NULL, sterr);
			}
			wait(&status);
			data->ret = WEXITSTATUS(status);
			if (fd_read)
				close(fd_read);
			fd_read = fd[0];
			close(fd[1]);
		}
		else if (((t_cmd*)lst->content)->sep_0 == '|')
		{
			pid = fork();
			if (pid == 0)
			{
				dup2(fd_read, STDIN_FILENO);
				close(fd_read);
				if (check_if_redir(((t_cmd*)lst->content)))
					redir_manager(((t_cmd*)lst->content), data, envp);
				else
				{
					if (!create_args_str((t_cmd*)lst->content))
						ft_exit(data, (t_cmd*)lst->content);
					cmd_caller(((t_cmd*)lst->content), data, envp);
				}
				exit(data->ret);
			}
			else if (pid < 0)
			{
				sterr = strerror(errno);
				error_msn(NULL, NULL, sterr);
			}
			wait(&status);
			data->ret = WEXITSTATUS(status);
			close(fd_read);
			fd_read = 0;
		}
		lst = lst->next;
	}
}

t_letter	*line_to_struct(char *str, int len)
{
	int			i;
	int			j;
	int			quote;
	t_letter	*line;

	i = 0;
	j = 0;
	quote = 0;
	//printf("len: %d, origi: %d\n", len, strlen(str));
	line = malloc((len + 1) * sizeof(t_letter));
	if (!line)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' && quote != 2)
		{
			if (!quote)
				quote = 1;
			else if (quote == 1)
				quote = 0;
			line[j].esc = 0;
		}
		else if (str[i] == '"' && quote != 1)
		{
			if (!quote)
				quote = 2;
			else if (quote == 2)
				quote = 0;
			line[j].esc = 0;
		}
		else if (str[i] == '\\' && (!quote || (quote == 2 && (str[i + 1] == '$' || str[i + 1] == '\\' || str[i + 1] == '"'))))
		{
			i++;
			line[j].esc = 1;
		}
		else
		{
			if (quote == 1 || (quote == 2 && str[i] != '$' && str[i] != '\\' && str[i] != '"'))
				line[j].esc = 1;
			else
				line[j].esc = 0;
		}
		line[j].c = str[i];
		i++;
		j++;
	}
	line[j].c = '\0';
	/*i = 0;
	while (i < len)
	{
		printf("str: %c esc: %d\n", line[i].c, line[i].esc);
		i++;
	}*/
	return (line);
}

void	parser(t_data *data, char *str, char **envp)
{
					//TODO: añadir parse errors de >>> <<< ><>< y eso
					//FIXME: echo hola ; $aaa | echo hola => tiene que hacer los dos comandos aunque el del medio esté vacío, no dar syntax error
	int   		i;
	int			len;
	t_list		*new;
	t_cmd		*com;
	//t_letter	*line;

	i = 0;
	data->line = NULL; 
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
