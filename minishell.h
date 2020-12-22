/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:36:50 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/12/22 11:52:49 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"

typedef struct	s_env
{
	char		*id;
	char		*value;
}				t_env;

void	ft_echo(char *str);
void    ft_env(t_list *head);
void    ft_exit(t_list **head);
void    parse_commands(char *str, t_list *head);

#endif
