/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 11:28:42 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/01/25 12:18:10 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_list *head, char *str)
{
	t_list	*lst;
	int		i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] != '\n')
	{
		write(1, "env: too many arguments\n", 24);
		return ;
	}
	lst = head;
	while (lst)
	{
		write(1, ((t_env*)lst->content)->id,
			ft_strlen(((t_env*)lst->content)->id));
		write(1, "=", 1);
		write(1, ((t_env*)lst->content)->value,
			ft_strlen(((t_env*)lst->content)->value));
		write(1, "\n", 1);
		lst = lst->next;
	}
}
