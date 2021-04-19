/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:26:21 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/04/19 13:56:39 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_in_env(t_list **env_head, char *str) //TODO: se puede usar en más sitios!! 
{
	t_list *list;

	list = *env_head;
	while (list)
	{
		if (!ft_strcmp(str, ((t_env*)list->content)->id))
			return (((t_env*)list->content)->value);
		list = list->next;
	}
	return (NULL);
}

int	is_space_quote_redir_or_endofcmd(t_letter c)
{
	if (c.c == ' ' || (c.c == '"' && !c.esc) || (c.c == '\'' && !c.esc) || (c.c == '<' && !c.esc) || (c.c == '>' && !c.esc)
	|| (c.c == ';' && !c.esc) || (c.c == '|' && !c.esc) || c.c == '\0')
		return (1);
	else
		return (0);
}

int	is_space_redir_or_endofcmd(t_letter c)
{
	if (c.c == ' ' || (c.c == '<' && !c.esc) || (c.c == '>' && !c.esc)
	|| (c.c == ';' && !c.esc) || (c.c == '|' && !c.esc) || c.c == '\0')
		return (1);
	else
		return (0);
}

int filter_empty_args(t_cmd *com)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < com->n_args)
	{
		if (com->args[i][0] != '\0')
			j++;
		i++;
	}
	tmp = malloc(j * sizeof(char *));
	if (!tmp)
		return (0);
	i = 0;
	j = 0;
	while (i < com->n_args)
	{
		if (com->args[i][0] != '\0')
		{
			tmp[j] = ft_strdup(com->args[i]);
			if (!tmp[j])
				return (0);
			j++;
		}
		free(com->args[i]);
		i++;
	}
	free(com->args);
	com->args = tmp;
	com->n_args = j;
	if (com->n_args == 0)
	{
		free(com->args);
		com->args = NULL;
	}
	return (1);
}

void	error_msn(char *cmd, char *str, char *txt)
{
	if (cmd && str && txt)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
		write(2, str, ft_strlen(str));
		write(2, ": ", 2);
		write(2, txt, ft_strlen(txt));
		write(2, "\n", 1);
	}
	else if (cmd && txt)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
		write(2, txt, ft_strlen(txt));
		write(2, "\n", 1);
	}
}