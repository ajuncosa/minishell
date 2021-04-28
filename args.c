/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:03:30 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/04/28 21:07:00 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_filter(t_cmd *com, int *found)
{
	int		n;
	char	*arg;

	n = 0;
	while (n < com->n_args)
	{
		arg = struct_to_str(com->args[n], 0, esc_strlen(com->args[n]));
		if (ft_strcmp(arg, ">") && ft_strcmp(arg, "<") && ft_strcmp(arg, ">>"))
		{
			com->cmd = arg;
			if (!com->cmd)
				return (-1);
			free(com->args[n]);
			*found = 1;
			return (n);
		}
		free(arg);
		n += 2;
	}
	return (n);
}

int	find_cmd(t_cmd *com)
{
	int			i;
	int			j;
	int			n;
	int			found;
	t_letter	**tmp;

	n = 0;
	found = 0;
	n = redir_filter(com, &found);
	if (n == -1)
		return (0);
	if (found)
		tmp = malloc((com->n_args - 1) * sizeof(t_letter *));
	else
		tmp = malloc(com->n_args * sizeof(t_letter *));
	if (!tmp)
		return (0);
	i = 0;
	j = 0;
	while (i < com->n_args)
	{
		if (found && i == n)
		{
			i++;
			continue ;
		}
		tmp[j] = esc_dup(com->args[i]);
		if (!tmp[j])
			return (0);
		free(com->args[i]);
		j++;
		i++;
	}
	free(com->args);
	com->args = tmp;
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

int	count_args(t_letter *str)
{
	int	i;
	int	n_args;

	i = 0;
	n_args = 0;
	while (str[i].c != '\0')
	{
		if ((str[i].c == ';' || str[i].c == '|') && !str[i].esc)
			break ;
		if ((str[i].c == '>' || str[i].c == '<') && !str[i].esc)
		{
			n_args++;
			while ((str[i].c == '>' || str[i].c == '<') && !str[i].esc)
				i++;
		}
		else
		{
			while (!is_space_redir_or_endofcmd(str[i]))
				i++;
			n_args++;
		}
		while (str[i].c == ' ' && !str[i].esc)
			i++;
	}
	return (n_args);
}

int	save_args(t_letter **str, t_cmd *com, int *start)
{
	int			end;
	int			n;
	t_letter	*tmp;

	tmp = quote_hunter(*str);
	if (!tmp)
		return (0);
	free(*str);
	*str = tmp;
	while ((*str)[*start].c == ' ' && !(*str)[*start].esc)
		*start += 1;
	n = 0;
	while (n < com->n_args)
	{
		end = *start;
		if (((*str)[*start].c == '>' || (*str)[*start].c == '<')
				&& !(*str)[*start].esc)
		{
			while (((*str)[end].c == '>' || (*str)[end].c == '<')
				&& !(*str)[end].esc)
				end++;
		}
		else
		{
			while (!is_space_redir_or_endofcmd((*str)[end]))
				end++;
		}
		com->args[n] = esc_substr(*str, *start, end - *start);
		if (!com->args[n])
			return (0);
		*start = end;
		while ((*str)[*start].c == ' ' && !(*str)[*start].esc)
			*start += 1;
		n++;
	}
	return (1);
}
