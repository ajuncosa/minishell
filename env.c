/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 11:28:42 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/04/27 18:12:57 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *data, char **args)
{
	t_list	*lst;
	int		i;

	i = 0;
	if (args != NULL)
	{
		error_msn("env", NULL, "too many arguments");
		data->ret = 1;
		return ;
	}
	lst = data->env_head;
	while (lst)
	{
		if (((t_env *)lst->content)->value != NULL)
			printf("%s=%s\n", ((t_env *)lst->content)->id,
				((t_env *)lst->content)->value);
		lst = lst->next;
	}
	data->ret = 0;
}
