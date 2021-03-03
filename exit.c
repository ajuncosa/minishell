/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 12:47:45 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/03 13:30:02 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_lst(void *env)
{
	free(((t_env*)env)->id);
	free(((t_env*)env)->value);
	free((t_env*)env);
}

void	ft_exit(t_list **head, char *user)
{
	free(user);
	ft_lstclear(head, &del_lst);
	exit(0);
}

void	del_lst_cmd(void *cmd)
{
	int j;
	
	free(((t_cmd*)cmd)->cmd);
	j = 0;
	while (j < ((t_cmd*)cmd)->n_args)
	{
		free(((t_cmd*)cmd)->args[j]);
		j++;
	}
	free(((t_cmd*)cmd)->args);
	free((t_cmd*)cmd);
}

void	ft_free_cmd(t_list **head)
{
	ft_lstclear(head, &del_lst_cmd);
}