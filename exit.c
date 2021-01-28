/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 12:47:45 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/01/28 11:40:40 by cruiz-de         ###   ########.fr       */
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
