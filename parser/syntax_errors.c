/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 12:07:52 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/05/18 14:18:35 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	end_of_cmd_flagcheck(t_letter *str, char *flag, int *i)
{
	if (*flag)
	{
		printf("syntax error near unexpected token `%c\'\n", str[*i].c);
		return (0);
	}
	if (str[*i].c == ';')
		*flag = ';';
	else if (str[*i].c == '|')
		*flag = '|';
	*i += 1;
	return (1);
}

int	redir_check(t_letter *str, char *flag, int *i)
{
	int	check;

	if (*flag == 'r')
	{
		printf("syntax error near unexpected token `%c\'\n", str[*i].c);
		return (0);
	}
	*flag = 'r';
	check = *i;
	if (str[*i].c == '>')
	{
		while (str[*i].c == '>' && !str[*i].esc && (*i - check) < 2)
			*i += 1;
	}
	else if (str[*i].c == '<')
	{
		while (str[*i].c == '<' && !str[*i].esc && (*i - check) < 1)
			*i += 1;
	}
	if ((str[*i].c == '>' || str[*i].c == '<') && !str[*i].esc)
	{
		printf("syntax error near unexpected token `%c\'\n", str[*i - 1].c);
		return (0);
	}
	return (1);
}

int	flag_loop(t_letter *str, char *flag, int *i)
{
	while (str[*i].c != '\0')
	{
		if ((str[*i].c == ';' || str[*i].c == '|') && !str[*i].esc)
		{
			if (!end_of_cmd_flagcheck(str, flag, i))
				return (0);
		}
		else if ((str[*i].c == '>' || str[*i].c == '<') && !str[*i].esc)
		{
			if (!redir_check(str, flag, i))
				return (0);
		}
		else
		{
			*flag = 0;
			while (!is_space_redir_or_endofcmd(str[*i]))
				*i += 1;
		}
		while (str[*i].c == ' ' && !str[*i].esc)
			*i += 1;
	}
	return (1);
}

int	syntax_errors(t_letter *str)
{
	int		i;
	char	flag;

	i = 0;
	flag = 0;
	while (str[i].c == ' ' && !str[i].esc)
		i++;
	if ((str[i].c == ';' || str[i].c == '|') && !str[i].esc)
	{
		printf("syntax error near unexpected token `%c\'\n", str[i].c);
		return (0);
	}
	if (!flag_loop(str, &flag, &i))
		return (0);
	if (flag == '|')
	{
		printf("Error: open pipe\n");
		return (0);
	}
	if (flag == 'r')
	{
		printf("syntax error near unexpected token `newline\'\n");
		return (0);
	}
	return (1);
}
