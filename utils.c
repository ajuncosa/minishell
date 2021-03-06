/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:26:21 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/05/04 13:30:51 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_in_env(t_list **env_head, char *str)
{
	t_list	*list;

	list = *env_head;
	while (list)
	{
		if (!ft_strcmp(str, ((t_env *)list->content)->id))
			return (((t_env *)list->content)->value);
		list = list->next;
	}
	return (NULL);
}

t_letter	*quote_hunter(t_letter *str)
{
	int			i;
	int			j;
	t_letter	*new;

	if (!str)
		return (NULL);
	new = malloc(sizeof(t_letter) * (esc_strlen(str) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i].c)
	{
		if (!((str[i].c == '\'' || str[i].c == '"') && !str[i].esc))
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j].c = '\0';
	return (new);
}

int	create_args_str(t_cmd *com)
{
	int	i;

	if (com->n_args > 0)
	{
		com->args_str = malloc(com->n_args * sizeof(char *));
		if (!com->args_str)
			return (0);
	}
	i = 0;
	while (i < com->n_args)
	{
		com->args_str[i] = struct_to_str(com->args[i], 0,
				esc_strlen(com->args[i]));
		free(com->args[i]);
		i++;
	}
	free(com->args);
	com->args = NULL;
	return (1);
}

int	is_space_redir_or_endofcmd(t_letter c)
{
	if ((c.c == ' ' && !c.esc) || (c.c == '<' && !c.esc)
		|| (c.c == '>' && !c.esc) || (c.c == ';' && !c.esc)
		|| (c.c == '|' && !c.esc) || c.c == '\0')
		return (1);
	else
		return (0);
}

void	free_str_array(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
