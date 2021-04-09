/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 11:28:42 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/04/09 12:58:45 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_data *data, char **args)
{
	t_list	*lst;
	int		i;

	i = 0;
	if (args != NULL)
	{
		write(2, "env: ", 6);
		write(2, args[0], ft_strlen(args[0]));
		write(2, ": ", 2);
		write(2, "No such file or directory\n", 27);
		return (1);
	}
	lst = data->env_head;
	while (lst)
	{
		if (((t_env*)lst->content)->value != NULL)
			printf("%s=%s\n",((t_env*)lst->content)->id, ((t_env*)lst->content)->value);
		lst = lst->next;
	}
	return (0);
}
