/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 13:29:19 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/04/29 13:33:42 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_alloc_init(t_data *data, t_cmd **com, t_list **new)
{
	*com = malloc(sizeof(t_cmd));
	if (!*com)
		ft_exit(data, *com);
	*new = ft_lstnew(*com);
	if (!*new)
		ft_exit(data, *com);
	(*com)->sep_0 = '0';
	(*com)->sep_1 = '0';
	(*com)->args = NULL;
	(*com)->args_str = NULL;
	(*com)->cmd = NULL;
}

int	countalloc_args(t_cmd *com, t_data *data, t_list *new, t_letter *line)
{
	com->n_args = count_args(line);
	if (com->n_args == -1)
	{
		free(new);
		free(com);
		free(data->line);
		ft_lstclear(&data->cmd_head, &del_lst_cmd);
		data->ret = 258;
		return (-1);
	}
	else if (com->n_args == 0)
	{
		free(new);
		free(com);
		return (0);
	}
	else if (com->n_args > 0)
	{
		com->args = malloc(com->n_args * sizeof(t_letter *));
		if (!com->args)
			ft_exit(data, com);
	}
	return (1);
}

int	find_arg_seps(t_data *data, t_cmd *com, int i, int sep)
{
	if (sep == 0)
	{
		if ((data->line[i].c == ';' || data->line[i].c == '|')
			&& !data->line[i].esc)
		{
			com->sep_0 = data->line[i].c;
			i++;
		}
	}
	else
	{
		if ((data->line[i].c == ';' || data->line[i].c == '|')
			&& !data->line[i].esc)
			com->sep_1 = data->line[i].c;
	}
	return (i);
}

void	save_cmd_args(t_data *data, t_cmd *com, int *i)
{
	if (!(save_args(&data->line, com, i)))
		ft_exit(data, com);
	if (!find_cmd(com))
		ft_exit(data, com);
}
