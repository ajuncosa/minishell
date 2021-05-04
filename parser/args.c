/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:03:30 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/05/04 13:45:36 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	increment_end(int *start, t_letter **str)
{
	int	end;

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
	return (end);
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
		end = increment_end(start, str);
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
