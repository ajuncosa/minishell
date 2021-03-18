/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 11:28:42 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/18 19:18:17 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_list **head, char **args)
{
	t_list	*lst;
	int		i;

	i = 0;
	if (args != NULL)
	{
		write(1, "env: too many arguments\n", 24);
		return (1);
	}
	lst = *head;
	while (lst)
	{
		if (((t_env*)lst->content)->value != NULL)
			printf("%s=%s\n",((t_env*)lst->content)->id, ((t_env*)lst->content)->value);
		lst = lst->next;
	}
	return (0);
}
