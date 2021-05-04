/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:11:43 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/05/04 12:36:42 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_redir(t_cmd *com)
{
	int		i;
	char	*arg;

	i = 0;
	while (i < com->n_args)
	{
		arg = struct_to_str(com->args[i], 0, esc_strlen(com->args[i]));
		if ((!ft_strcmp(arg, ">") || !ft_strcmp(arg, ">>")
				|| !ft_strcmp(arg, "<")) && !com->args[i][0].esc)
		{
			free(arg);
			return (1);
		}
		free(arg);
		i++;
	}
	return (0);
}

void	count_redir(t_cmd *com)
{
	int		i;
	char	*arg;

	i = 0;
	com->n_redir = 0;
	while (i < com->n_args)
	{
		arg = struct_to_str(com->args[i], 0, esc_strlen(com->args[i]));
		if ((!ft_strcmp(arg, ">") || !ft_strcmp(arg, ">>")
				|| !ft_strcmp(arg, "<")) && !com->args[i][0].esc)
			com->n_redir++;
		free(arg);
		i++;
	}
}

int	create_redir_array(t_cmd *com, t_redir *redir, int i, int j)
{
	if ((!esc_cmp(com->args[i], ">") || !esc_cmp(com->args[i], ">>")
				|| !esc_cmp(com->args[i], "<")) && !com->args[i][0].esc)
	{
		redir->type = struct_to_str(com->args[i], 0, esc_strlen(com->args[i]));
		if (!redir->type)
			return (0);
		redir->file = struct_to_str(com->args[i + 1], 0, esc_strlen(com->args[i + 1]));;
		if (!redir->file)
			return (0);
		return (1);
	}
	else
	{
		com->args_str[j] = struct_to_str(com->args[i], 0, esc_strlen(com->args[i]));
		if (!com->args_str[j])
			return (0);
		return (2);
	}
}

int	cleaner_loop(t_cmd *com, t_redir *redir)
{
	int		i;
	int		j;
	int		k;
	int		r;

	i = 0;
	j = 0;
	k = 0;
	while (i < com->n_args)
    {
		r = create_redir_array(com, &redir[k], i, j);
		free(com->args[i]);
		if (r == 0)
			return (0);
		else if (r == 1)
		{
			free(com->args[i + 1]);
			k++;
			i += 2;
		}
		else if (r == 2)
		{
			i++;
			j++;
		}
    }
	return (1);
}

int	arg_cleaner(t_cmd *com, t_redir *redir)
{
	int		n_del;

	n_del = com->n_redir * 2;
	if ((com->n_args - n_del) > 0)
	{
		com->args_str = malloc((com->n_args - n_del) * sizeof(char *));
		if (!com->args_str)
			return (0);
	}
	if (!cleaner_loop(com, redir))
		return (0);
	free(com->args);
	com->args = NULL;
	com->n_args = com->n_args - n_del;
	return (1);
}
