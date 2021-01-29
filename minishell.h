/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:36:50 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/01/29 11:08:17 by ajuncosa         ###   ########.fr       */
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

void	ft_echo(char *str);
void	ft_env(t_list **head, char *str);
void	ft_exit(t_list **head, char *user);
int		parse_commands(char *str, t_list **head, int ret,char *user);
void	ft_pwd(char *str);
void	ft_export(t_list **head, char *str);
void	ft_unset(t_list **head, char *str);
void	del_lst(void *env);
void	ft_cd(char *str, char *user);
void	ft_ls(void);

#endif
