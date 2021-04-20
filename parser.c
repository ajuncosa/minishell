/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:53:05 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/04/20 11:49:20 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_cmd(t_cmd *com)
{
	int 	i;
	int		j;
	int		n;
	int		found;
	char	**tmp;

	n = 0;
	found = 0;
	while (n < com->n_args)
	{
		if (strcmp(com->args[n], ">") && strcmp(com->args[n], "<") && strcmp(com->args[n], ">>"))
		{
			com->cmd = ft_strdup(com->args[n]);
			if (!com->cmd)
				return (0);
			free(com->args[n]);
			found = 1;
			break;
		}
		n += 2;
	}
	if (found)
		tmp = malloc((com->n_args - 1) * sizeof(char *));
	else
		tmp = malloc(com->n_args * sizeof(char *));
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
		tmp[j] = ft_strdup(com->args[i]);
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
	
	i = 0;
	n_args = 0;
	while (str[i].c != '\0')
	{
		if ((str[i].c == ';' || str[i].c == '|') && !str[i].esc)
			break ;
		if (str[i].c == '"' && !str[i].esc)
		{
			i++;
			while (str[i].c != '\0')
			{
				if (str[i].c == '"' && !str[i].esc)
					break;
				i++;
			}
			if (str[i].c != '"')
			{
				write(2, "Error: open dquote\n", 20);
				return (-1);
			}
			i++;
			if (is_space_redir_or_endofcmd(str[i]))
				n_args++;
		}
		else if (str[i].c == '\'' && !str[i].esc)
		{
			i++;
			while (str[i].c != '\'' && str[i].c != '\0')
				i++;
			if (str[i].c != '\'')
			{
				write(2, "Error: open quote\n", 19);
				return (-1);
			}
			i++;
			if (is_space_redir_or_endofcmd(str[i]))
				n_args++;
		}
		else if ((str[i].c == '>' || str[i].c == '<') && !str[i].esc)
		{
			n_args++;
			while((str[i].c == '>' || str[i].c == '<') && !str[i].esc)
				i++;
		}
		else
		{
			while (!is_space_quote_redir_or_endofcmd(str[i]))
				i++;
			if (str[i].c != '"' && str[i].c != '\'')
				n_args++;
		}
		while (str[i].c == ' ')
			i++;
	}
	return (n_args);
}

int		save_args(t_letter *str, int n_args, char **args, int *start, t_data *data)
{
	int		end;
	int		space;
	int		n;
	char	*tmp1;
	char	*tmp2;

	n = 0;
	space = 1;
	while (n < n_args)
	{
		if (str[*start].c == '"' && !str[*start].esc)
		{
			*start += 1;
			end = *start;
			while (str[end].c != '\0')	
			{
				if (str[end].c == '"' && !str[end].esc)
					break;
				end++;
			}
			/*if (!space)
			{
				tmp1 = ft_substr(str, *start, end - *start);
				if (!tmp1)
					return (0);
				if (!dollar_finder(&data->env_head, &tmp1, data->ret))
					return (0);
				tmp2 = ft_strjoin(args[n], tmp1);
				if (!tmp2)
					return (0);
				free(args[n]);
				free(tmp1);
				args[n] = tmp2;
			}
			else
			{
				if (!(args[n] = ft_substr(str, *start, end - *start)))
					return (0);
				if (!dollar_finder(&data->env_head, &args[n], data->ret))
					return (0);
			}*/
			*start = end + 1;
		}
		else if (str[*start].c == '\'' && !str[*start].esc)
		{
			*start += 1;
			end = *start;
			while (str[end].c != '\'' && str[end].c != '\0')
				end++;
			/*if (!space)
			{	
				tmp1 = ft_substr(str, *start, end - *start);
				if (!tmp1)
					return (0);
				tmp2 = ft_strjoin(args[n], tmp1);
				if (!tmp2)
					return (0);
				free(args[n]);
				free(tmp1);
				args[n] = tmp2;
			}
			else
			{
				if (!(args[n] = ft_substr(str, *start, end - *start)))
					return (0);
			}*/
			*start = end + 1;
		}
		else if ((str[*start].c == '>' || str[*start].c == '<') && !str[*start].esc)
		{
			end = *start;
			while ((str[end].c == '>' || str[end].c == '<') && !str[end].esc)
				end++;
			/*if (!(args[n] = ft_substr(str, *start, end - *start)))
				return (0);*/
			*start = end;
		}
		else
		{
			end = *start;
			while (!is_space_quote_redir_or_endofcmd(str[end]))
				end++;
			/*if (!space)
			{	
				tmp1 = ft_substr(str, *start, end - *start);
				if (!tmp1)
					return (0);
				if (!dollar_finder(&data->env_head, &tmp1, data->ret))	
					return (0);
				tmp2 = ft_strjoin(args[n], tmp1);
				if (!tmp2)
					return (0);
				free(args[n]);
				free(tmp1);
				args[n] = tmp2;
			}
			else
			{
				if (!(args[n] = ft_substr(str, *start, end - *start)))
					return (0);
				if (!dollar_finder(&data->env_head, &args[n], data->ret))
					return (0);
			}*/
			*start = end;
		}
		if (!is_space_redir_or_endofcmd(str[*start])
			&& !((str[*start - 1].c == '>' || str[*start - 1].c == '<') && !str[*start - 1].esc))
			space = 0;
		else
		{
			space = 1;
			while (str[*start].c == ' ')
				*start += 1;
			n++;
		}
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
		ft_pwd(data, com->args);
	else if (!ft_strcmp(com->cmd, "export"))
		ft_export(data, com);
	else if (!ft_strcmp(com->cmd, "cd"))
		ft_cd(data, com);
	else if (!ft_strcmp(com->cmd, "unset"))
		ft_unset(data, com);
	else if (!ft_strcmp(com->cmd, "env"))
		ft_env(data, com->args);
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
				cmd_caller(((t_cmd*)lst->content), data, envp);			
		}
		if (((t_cmd*)lst->content)->sep_1 == '|')	//FIXME: si hay pipes con un comando que no existe, tiene que dar el mensaje de command not found aunque el comando que no existe sea el primero. e.g. "fasdjh | ls"; si es el segundo el que no existe, no hace el primero (sólo imprime el error del segundo, el nuestro esto lo hace bien); si no existe ninguno, pone todos los mensajes de error
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
					cmd_caller(((t_cmd*)lst->content), data, envp);
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
					cmd_caller(((t_cmd*)lst->content), data, envp);
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

t_letter	*str_to_struct(char *str)
{
	int			i;
	int			j;
	int			len;
	int			quote;
	t_letter	*line;

	i = 0;
	j = 0;
	quote = 0;
	len = esc_size(str);
	line = malloc((len + 1) * sizeof(t_letter));
	if (!line)
		return (NULL);
	while (str[i])		//TODO: error open "\"
	{
		if (str[i] == '\'')
		{
			if (!quote)
				quote = 1;
			else
				quote = 0;
		}
		line[j].esc = 0;
		if (str[i] == '\\' && !quote)
		{
			i++;
			line[j].esc = 1;
		}
		line[j].c = str[i];
		i++;
		j++;
	}
	line[j].c = '\0';
	return (line);
	/*i = 0;
	while (i < len)
	{
		printf("str: %c esc: %d\n", line[i].c, line[i].esc);
		i++;
	}
	*/
}

void	parser(t_data *data, char *str, char **envp)
{					//FIXME: errores a gestionar: {< | hola} {ls ; <} {< ;}  {<} {>} {<  <} {> >} {=>}, si pones {>|} ignora el pipe (creo), si acaba en redirección
					//TODO: añadir parse errors de >>> <<< ><>< y eso
	int   		i;
	t_list		*new;
	t_cmd		*com;
	t_letter	*line;

	i = 0;
	com = NULL;
	data->cmd_head = NULL;
	line = str_to_struct(str);
	if (!line)
		ft_exit(data, com);
	while (line[i].c != '\0')
	{
		// ALOCAR LISTA Y CONTENT
		if (!(new = malloc(sizeof(t_list))))
			ft_exit(data, com);
		if (!(com = malloc(sizeof(t_cmd))))
			ft_exit(data, com);
		new->content = com;

		// INICIALIZAR COSAS
		((t_cmd*)new->content)->sep_0 = '0';
		((t_cmd*)new->content)->sep_1 = '0';
		((t_cmd*)new->content)->args = NULL;
		((t_cmd*)new->content)->cmd = NULL;
	
		while (line[i].c == ' ')
			i++;

		// BUSCAR sep_0 (el separador de comandos (; o |) que viene antes del comando actual)
		if ((line[i].c == ';' || line[i].c == '|') && !line[i].esc)
		{
			if (!data->cmd_head)
			{
				printf("syntax error near unexpected token `%c\'\n", line[i].c);
				free(new);
				free(com);
				data->ret = 258;
				return ;
			}
			else
				((t_cmd*)new->content)->sep_0 = line[i].c;
			i++;
			while (line[i].c == ' ')
				i++;
			if ((line[i].c == ';' || line[i].c == '|') && !line[i].esc)
			{
				printf("syntax error near unexpected token `%c\'\n", line[i].c);
				free(new);
				free(com);
				ft_lstclear(&data->cmd_head, &del_lst_cmd);
				data->ret = 258;
				return ;
			}
			if (((t_cmd*)new->content)->sep_0 == '|' && line[i].c == '\0')
			{
				printf("Error: open pipe\n");
				free(new);
				free(com);
				ft_lstclear(&data->cmd_head, &del_lst_cmd);
				data->ret = 258;
				return ;
			}
		}
		// CONTAR ARGUMENTOS Y ALOCAR ARGS
		((t_cmd*)new->content)->n_args = count_args(&line[i]);
		printf("n_args: %d\n", ((t_cmd*)new->content)->n_args);
		if (((t_cmd*)new->content)->n_args == -1)
		{
			free(new);
			free(com);
			ft_lstclear(&data->cmd_head, &del_lst_cmd);
			data->ret = 0;
			return ;
		}
		if (((t_cmd*)new->content)->n_args == 0)
		{
			free(new);
			free(com);
			continue;
		}
		if (((t_cmd*)new->content)->n_args > 0)
		{
			if (!(((t_cmd*)new->content)->args = malloc(((t_cmd*)new->content)->n_args * sizeof(char *))))
				ft_exit(data, com);
		}
		// GUARDAR ARGUMENTOS
		if (!(save_args(line, ((t_cmd*)new->content)->n_args, ((t_cmd*)new->content)->args, &i, data)))
			ft_exit(data, com);

		// CREAR ARRAY DE ARGS NUEVO ElIMINANDO LAS $ QUE NO EXISTEN
		/*if (!filter_empty_args((t_cmd*)new->content))
			ft_exit(data, com);
		if (((t_cmd*)new->content)->n_args == 0)
		{
			free(new);
			free(com);
			continue;
		}

		// BUSCAR COMANDO Y GUARDAR POR SEPARADO
		if (!find_cmd((t_cmd*)new->content))
			ft_exit(data, com);

		// GUARDAR sep_1
		if (str[i] == ';' || str[i] == '|')
			 ((t_cmd*)new->content)->sep_1 = str[i];

		//GUARDAR COMANDO EN LISTA
		ft_lstadd_back(&data->cmd_head, new);*/
	}

	//HACER  COMANDOS
	//cmd_manager(data, envp);
	
	//REINICIAR PID PARA PODER HACER CTRL-C CUANDO UN PROCESO DEJE LA PID CAMBIADA AL TERMINAR
	pid = -1;

	// FREES DE ESTA LÍNEA DE COMANDOS
	ft_lstclear(&data->cmd_head, &del_lst_cmd);
}
