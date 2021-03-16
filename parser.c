/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:53:05 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/16 13:42:13 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_cmd(char *str, int *i)	//FIXME: "cmd>file" (sin espacios) no funciona, hay que separar el comando por < y > también
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
			i++;
			if (str[i] == ' ' || str[i] == ';' || str[i] == '|' || str[i] == '\n' || str[i] == '\0')
				n_args++;
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
			i++;
			if (str[i] == ' ' || str[i] == ';' || str[i] == '|' || str[i] == '\n' || str[i] == '\0')
				n_args++;
		}
		else if (str[i] == '>' || str[i] == '<')
		{
			n_args++;
			while(str[i] == '>' || str[i] == '<')
				i++;
		}
		else
		{
			while (str[i] != ' ' && str[i] != '"' && str[i] != '\''
				&& str[i] != '<' && str[i] != '>' && str[i] != '\n'
				&& str[i] != ';' && str[i] != '|' && str[i] != '\0')
				i++;
			if (str[i] != '"' && str[i] != '\'')
				n_args++;
		}
		while (str[i] == ' ')
			i++;
	}
	return (n_args);
}

int		save_args(char *str, int n_args, char **args, int *start)
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
		if (str[*start] == '"')
		{
			*start += 1;
			end = *start;
			while (str[end] != '"' && str[end] != '\n' && str[end] != '\0')
				end++;
			if (!space)
			{	
				tmp1 = ft_substr(str, *start, end - *start);
				tmp2 = ft_strjoin(args[n], tmp1);
				free(args[n]);
				free(tmp1);
				args[n] = tmp2;
			}
			else
			{
				if (!(args[n] = ft_substr(str, *start, end - *start)))
					return (0);
			}
			*start = end + 1;
		}
		else if (str[*start] == '\'')
		{
			*start += 1;
			end = *start;
			while (str[end] != '\'' && str[end] != '\n' && str[end] != '\0')
				end++;
			if (!space)
			{	
				tmp1 = ft_substr(str, *start, end - *start);
				tmp2 = ft_strjoin(args[n], tmp1);
				free(args[n]);
				free(tmp1);
				args[n] = tmp2;
			}
			else
			{
				if (!(args[n] = ft_substr(str, *start, end - *start)))
					return (0);
			}
			*start = end + 1;
		}
		else if (str[*start] == '>' || str[*start] == '<')
		{
			end = *start;
			while (str[end] == '>' || str[end] == '<')
				end++;
			if (!(args[n] = ft_substr(str, *start, end - *start)))
				return (0);
			*start = end;
		}
		else
		{
			end = *start;
			while (str[end] != ' ' && str[end] != '"' && str[end] != '\''
				&& str[end] != '>' && str[end] != '<'
				&& str[end] != '\n'  && str[end] != ';' && str[end] != '|'
				&& str[end] != '\0')
				end++;
			if (!space)
			{	
				tmp1 = ft_substr(str, *start, end - *start);
				tmp2 = ft_strjoin(args[n], tmp1);
				free(args[n]);
				free(tmp1);
				args[n] = tmp2;
			}
			else
			{
				if (!(args[n] = ft_substr(str, *start, end - *start)))
					return (0);
			}
			*start = end;
		}
		if (str[*start] != ' ' && str[*start] != '>' && str[*start] != '<'
			&& str[*start] != ';' && str[*start] != '|' && str[*start] != '\0'
			&& str[*start] != '\n' && str[*start - 1] != '>' && str[*start - 1] != '<')
			space = 0;
		else
		{
			space = 1;
			while (str[*start] == ' ')
				*start += 1;
			n++;
		}
	}
	return (1);
}

int	cmd_caller(t_cmd *com, t_list **env_head, t_list **cmd_head, int ret, char *user) //FIXME: en los strncmp hay que comprobar la len del más largo, si no funcionará con "ech" por ejemplo
{
	int len;

	len = ft_strlen(com->cmd);
	if (!ft_strncmp(com->cmd, "echo", len)) //probar si funcionan espacios
		return(ft_echo(com));
	if (!ft_strncmp(com->cmd, "pwd", len))
		return(ft_pwd(com->args));
	else if (!ft_strncmp(com->cmd, "export", len))
		return(ft_export(env_head, com));
	else if (!ft_strncmp(com->cmd, "cd", len))
		return(ft_cd(com, user));
	else if (!ft_strncmp(com->cmd, "unset", len))
		return(ft_unset(env_head, com));
	else if (!ft_strncmp(com->cmd, "env", len))
		return(ft_env(env_head, com->args));
	else if (!ft_strncmp(com->cmd, "$?", len))
		return(ft_exit_status(ret));
	else if (!ft_strncmp(com->cmd, "exit", len))
		ft_exit(env_head, cmd_head, user);
	else
		return (ft_cmd(com));
	return (0);
}

int	cmd_manager(t_list **cmd_head, t_list **env_head, int ret, char *user)
{
	int		fd[2];
	int		pid;
	char 	*sterr;
	int		fd_read;
	t_list	*lst;
	int		r;

	lst = *cmd_head;
	fd_read = 0;
	while (lst)
	{
		if (((t_cmd*)lst->content)->sep_0 != '|' && ((t_cmd*)lst->content)->sep_1 != '|')
		{
			if (check_if_redir(((t_cmd*)lst->content)))
				r = redir_manager(((t_cmd*)lst->content), env_head, cmd_head, ret, user);
			else
				r = cmd_caller(((t_cmd*)lst->content), env_head, cmd_head, ret, user);
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
					r = redir_manager(((t_cmd*)lst->content), env_head, cmd_head, ret, user);
				else
					r = cmd_caller(((t_cmd*)lst->content), env_head, cmd_head, ret, user);
				exit(0);
			}
			else if (pid < 0)
			{
				sterr = strerror(errno);
				write(2, sterr, ft_strlen(sterr));
				write(2, "\n", 1);
			}
			wait(NULL);
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
					r = redir_manager(((t_cmd*)lst->content), env_head, cmd_head, ret, user);
				else
					r = cmd_caller(((t_cmd*)lst->content), env_head, cmd_head, ret, user);
				exit(0);
			}
			else if (pid < 0)
			{
				sterr = strerror(errno);
				write(2, sterr, ft_strlen(sterr));
				write(2, "\n", 1);
			}
			wait(NULL);
			close(fd_read);
			fd_read = 0;
		}
		lst = lst->next;
	}
	return (r);
}

int		parser(char *str, t_list **env_head, int ret, char *user)	//TODO: gestionar valores de retorno aquí, en cmd_manager y en todas las funciones de comandos
{																	//FIXME: el comando también puede venir entre comillas
																	//TODO: añadir parse errors de >>> <<< ><>< y eso (y terminar los de | y ;)
	int     i;
	t_list	*cmd_head;
	t_list	*new;
	t_cmd	*com;
	int		r;

	i = 0;
	cmd_head = NULL;
	while (str[i] != '\n')
	{
		// ALOCAR LISTA Y CONTENT
		if (!(new = malloc(sizeof(t_list))))
			ft_exit(env_head, &cmd_head, user);
		if (!(com = malloc(sizeof(t_cmd))))
			ft_exit(env_head, &cmd_head, user);
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
			ft_exit(env_head, &cmd_head, user);
		while (str[i] == ' ')
			i++;

		// CONTAR ARGUMENTOS Y ALOCAR ARGS
		((t_cmd*)new->content)->n_args = count_args(&str[i]);
		if (((t_cmd*)new->content)->n_args == -1)
		{
			ft_lstclear(&cmd_head, &del_lst_cmd);
			return (0);
		}
		if (((t_cmd*)new->content)->n_args > 0)
		{
			if (!(((t_cmd*)new->content)->args = malloc(((t_cmd*)new->content)->n_args * sizeof(char *))))
				ft_exit(env_head, &cmd_head, user);
		}

		// GUARDAR ARGUMENTOS
		if (!(save_args(str, ((t_cmd*)new->content)->n_args, ((t_cmd*)new->content)->args, &i)))
			ft_exit(env_head, &cmd_head, user);
															//TODO: si ponen ; y | a la vez e.g. "ls ;| wc" tiene que dar error
		// GUARDAR sep_1									//TODO: si la línea acaba en | sin nada detrás se queda el pipe abierto (devolver un error como con las comillas)
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

	//HACER  COMANDOS
	r = cmd_manager(&cmd_head, env_head, ret, user);
	
	// FREES DE ESTA LÍNEA DE COMANDOS
	ft_lstclear(&cmd_head, &del_lst_cmd);
	return (r);
}
