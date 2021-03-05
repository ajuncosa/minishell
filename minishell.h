/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:36:50 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/05 13:23:02 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <dirent.h>
# include "gnl/get_next_line.h"
# include "ft_printf/libftprintf.h"

typedef struct	s_env
{
	char		*id;
	char		*value;
}				t_env;

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	char	sep_0;
	char	sep_1;
	int		n_args;
}				t_cmd;

int		ft_echo(char *str);
int		ft_env(t_list **head, char *str);
void	ft_exit(t_list **head, char *user);
int		cmd_manager(char *str, t_list **env_head, int ret, char *user);
int		parser(char *str, t_list **env_head, int ret, char *user);
// int		parse_commands(char *str, t_list **head, int ret,char *user);
int		ft_pwd(char *com, char **args);
int		ft_export(t_list **head, char *str);
int		ft_unset(t_list **head, char *str);
void	del_lst(void *env);
void	del_lst_cmd(void *cmd);
void	ft_free_cmd(t_list **head);
int		ft_cd(char *str, char *user);
int		ft_exit_status(int ret);
int 	ft_cmd(char *str);

#endif
