/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:11:43 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/04/28 21:05:43 by ajuncosa         ###   ########.fr       */
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

int	arg_cleaner(t_cmd *com, t_redir *redir)
{
	int		i;
	int		j;
	int		k;
	int		n_del;
	char	*arg;

	n_del = com->n_redir * 2;
	if ((com->n_args - n_del) > 0)
	{
		com->args_str = malloc((com->n_args - n_del) * sizeof(char *));
		if (!com->args_str)
			return (0);
	}
	i = 0;
	j = 0;
	k = 0;
	while (i < com->n_args)
	{		
		arg = struct_to_str(com->args[i], 0, esc_strlen(com->args[i]));
		if ((!ft_strcmp(arg, ">") || !ft_strcmp(arg, ">>")
				|| !ft_strcmp(arg, "<")) && !com->args[i][0].esc)
		{
			redir[k].type = ft_strdup(arg);
			if (!redir[k].type)
				return (0);
			free(arg);
			arg = struct_to_str(com->args[i + 1], 0,
					esc_strlen(com->args[i + 1]));
			redir[k].file = ft_strdup(arg);
			if (!redir[k].file)
				return (0);
			free(com->args[i]);
			k++;
			i++;
		}
		else
		{
			com->args_str[j] = ft_strdup(arg);
			if (!com->args_str[j])
				return (0);
			j++;
		}
		free(com->args[i]);
		free(arg);
		i++;
	}
	free(com->args);
	com->args = NULL;
	com->n_args = com->n_args - n_del;
	return (1);
}
