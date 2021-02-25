/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:36:50 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/02/25 13:12:33 by cruiz-de         ###   ########.fr       */
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
	char *cmd;
	char **args;
	char sep[2];
}				t_cmd;

int		ft_echo(char *str);
int		ft_env(t_list **head, char *str);
void	ft_exit(t_list **head, char *user);
int		parser(char *str, t_list **head, int ret, char *user);
// int		parse_commands(char *str, t_list **head, int ret,char *user);
int		ft_pwd(char *str);
int		ft_export(t_list **head, char *str);
int		ft_unset(t_list **head, char *str);
void	del_lst(void *env);
int		ft_cd(char *str, char *user);
int		ft_exit_status(int ret);
int 	ft_cmd(char *str);

#endif
