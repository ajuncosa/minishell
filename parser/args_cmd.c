/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:50:47 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/05/04 13:45:47 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_filter(t_cmd *com, int *found)
{
	int		n;
	char	*arg;

	n = 0;
	*found = 0;
	while (n < com->n_args)
	{
		arg = struct_to_str(com->args[n], 0, esc_strlen(com->args[n]));
		if (!arg)
			return (-1);
		if (ft_strcmp(arg, ">") && ft_strcmp(arg, "<") && ft_strcmp(arg, ">>"))
		{
			com->cmd = arg;
			free(com->args[n]);
			*found = 1;
			return (n);
		}
		free(arg);
		n += 2;
	}
	return (n);
}

int	replace_arg_array(t_cmd *com, int n, t_letter ***tmp, int found)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < com->n_args)
	{
		if (found && i == n)
		{
			i++;
			continue ;
		}
		(*tmp)[j] = esc_dup(com->args[i]);
		if (!(*tmp)[j])
			return (0);
		free(com->args[i]);
		j++;
		i++;
	}
	free(com->args);
	com->args = *tmp;
	return (1);
}

int	find_cmd(t_cmd *com)
{
	int			n;
	int			found;
	t_letter	**tmp;

	n = redir_filter(com, &found);
	if (n == -1)
		return (0);
	if (found)
		tmp = malloc((com->n_args - 1) * sizeof(t_letter *));
	else
		tmp = malloc(com->n_args * sizeof(t_letter *));
	if (!tmp)
		return (0);
	if (!replace_arg_array(com, n, &tmp, found))
		return (0);
	if (found)
	{
		com->n_args -= 1;
		if (com->n_args == 0)
		{
			free(com->args);
			com->args = NULL;
		}
	}
	return (1);
}
