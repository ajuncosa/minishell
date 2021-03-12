/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 12:47:45 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/12 17:51:37 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_lst(void *env)
{
	free(((t_env*)env)->id);
	free(((t_env*)env)->value);
	free((t_env*)env);
}

void	del_lst_cmd(void *cmd)
{
	int j;

	if (((t_cmd*)cmd)->cmd)
		free(((t_cmd*)cmd)->cmd);
	j = 0;
	while (j < ((t_cmd*)cmd)->n_args)
	{
		free(((t_cmd*)cmd)->args[j]);
		j++;
	}
	if (((t_cmd*)cmd)->args)
		free(((t_cmd*)cmd)->args);
	free((t_cmd*)cmd);
}

void	ft_exit(t_list **env_head, t_list **cmd_head, char *user)
{
	if (user)
		free(user);
	ft_lstclear(cmd_head, &del_lst_cmd);
	ft_lstclear(env_head, &del_lst);
	exit(0);
}