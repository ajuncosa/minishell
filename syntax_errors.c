/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 12:07:52 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/04/29 19:25:18 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_errors(t_letter *str)
{
	int		i;
	int		check;
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
	while (str[i].c != '\0')
	{
		if ((str[i].c == ';' || str[i].c == '|') && !str[i].esc)
		{
			if (flag)
			{
				printf("syntax error near unexpected token `%c\'\n", str[i].c);
				return (0);
			}
			if (str[i].c == ';')
				flag = ';';
			else if (str[i].c == '|')
				flag = '|';
			i++;
		}
		else if ((str[i].c == '>' || str[i].c == '<') && !str[i].esc)
		{
			if (flag)
			{
				printf("syntax error near unexpected token `%c\'\n", str[i].c);
				return (0);
			}
			flag = 'r';
			check = i;
			if (str[i].c == '>')
			{
				while (str[i].c == '>' && !str[i].esc && (i - check) < 2)
					i++;
			}
			else if (str[i].c == '<')
			{
				while (str[i].c == '<' && !str[i].esc && (i - check) < 1)
					i++;
			}
			if ((str[i].c == '>' || str[i].c == '<') && !str[i].esc)
			{
				printf("syntax error near unexpected token `%c\'\n", str[i - 1].c);
				return (0);
			}
		}
		else
		{
			flag = 0;
			while (!is_space_redir_or_endofcmd(str[i]))
				i++;
		}
		while (str[i].c == ' ' && !str[i].esc)
			i++;
	}
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
