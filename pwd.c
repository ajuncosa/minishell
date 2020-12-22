/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 12:51:16 by ajuncosa          #+#    #+#             */
/*   Updated: 2020/12/22 13:23:58 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_list *head, char *str)
{
	t_list	*lst;
	char	*pwd;
	int		i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] != '\n')
	{
		write(1, "pwd: too many arguments\n", 24);
		return ;
	}
	lst = head;
	while (lst)
	{
		if (!ft_strncmp(((t_env*)lst->content)->id, "PWD", 3))
		{
			pwd = ((t_env*)lst->content)->value;
			write(1, pwd, ft_strlen(pwd));
			write(1, "\n", 1);
			return ;
		}
		lst = lst->next;
	}
}
