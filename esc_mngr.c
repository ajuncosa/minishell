/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_mngr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:09:37 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/04/30 19:27:25 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_flagger(char c, int quote)
{
	if (c == '\'' && quote != 2)
	{
		if (!quote)
			quote = 1;
		else if (quote == 1)
			quote = 0;
	}
	else if (c == '"' && quote != 1)
	{
		if (!quote)
			quote = 2;
		else if (quote == 2)
			quote = 0;
	}
	return (quote);
}

int	open_quote_checks(int quote, int n)
{
	if (quote == 1)
	{
		write(2, "Error: open quote\n", 18);
		return (-1);
	}
	else if (quote == 2)
	{
		write(2, "Error: open dquote\n", 19);
		return (-1);
	}
	return (n);
}

int	esc_size(char *str)
{
	int	quote;
	int	i;
	int	n;

	i = 0;
	n = 0;
	quote = 0;
	while (str[i])
	{
		quote = quote_flagger(str[i], quote);
		if (str[i] == '\\' && (!quote || (quote == 2 && (str[i + 1] == '$'
						|| str[i + 1] == '\\' || str[i + 1] == '"'))))
		{
			i++;
			if (str[i] == '\0')
			{
				write(2, "Error: open backslash\n", 23);
				return (-1);
			}
		}
		n++;
		i++;
	}
	return (open_quote_checks(quote, n));
}

t_letter	*line_to_struct(char *str, int len)
{
	int			i;
	int			j;
	int			quote;
	int			dollar;
	t_letter	*line;

	i = 0;
	j = 0;
	quote = 0;
	dollar = 0;
	line = malloc((len + 1) * sizeof(t_letter));
	if (!line)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '\'' && quote != 2) || (str[i] == '"' && quote != 1))
		{
			line[j].esc = 0;
			quote = quote_flagger(str[i], quote);
		}
		else if (str[i] == '\\' && (!quote || (quote == 2
					&& (str[i + 1] == '$' || str[i + 1] == '\\'
						|| str[i + 1] == '"'))))
		{
			i++;
			line[j].esc = 1;
		}
		else
		{
			if (dollar && !ft_isalnum(str[i]) && str[i] != '_')
				dollar = 0;
			if (!dollar && (quote == 1 || (quote == 2 && str[i] != '$'
						&& str[i] != '\\' && str[i] != '"')))
				line[j].esc = 1;
			else
			{
				line[j].esc = 0;
				if (str[i] == '$')
					dollar = 1;
			}
		}
		line[j].c = str[i];
		i++;
		j++;
	}
	line[j].c = '\0';
	return (line);
}
