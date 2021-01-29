/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:14:49 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/01/29 12:57:38 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_list **head, char *str)							//TODO: returns para $?
{
	t_list	*new;
	t_list	*list;
	t_env	*env;
	int		i;
	int		valid;
	int		len;
	int		start;

	valid = 0;
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0' || str[i] == '\n')
	{
		list = *head;
		while (list)
		{
			write(1, ((t_env*)list->content)->id, ft_strlen(((t_env*)list->content)->id));
			write(1, "=", 1);
			write(1, ((t_env*)list->content)->value, ft_strlen(((t_env*)list->content)->value));
			write(1, "\n", 1);
			list = list->next;
		}
		return (0);
	}
	start = i;
	if (!ft_isalpha(str[i]))
	{
		write(1, "Error: not an identifier\n", 25);
		return (1);
	}
	while (str[i])
	{
		if (!valid && str[i] == '=')
			valid = 1;
		if (str[i] == '=' && str[i - 1] == ' ')				/*FIXME: manage space after '=' */
		{
			if (str[i + 1] == ' ')
			{
				write(1, "bad assignment\n", 15);
				return (0);
			}
			else
			{
				write(1, "not found\n", 10);			/* TODO: añadir nombre de la var al error */
				return (1);
			}
		}
		i++;
	}
	if (!valid)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	i = start;
	len = 0;
	while (str[i] != '=')
	{
		i++;
		len++;
	}
	new = malloc(sizeof(t_list));
	env = malloc(sizeof(t_env));
	new->content = env;
	((t_env *)new->content)->id = ft_substr(str, start, len);
	list = *head;
	while (list)
	{
		if (!ft_strncmp(((t_env*)list->content)->id, ((t_env *)new->content)->id, len))
		{
			free(((t_env *)list->content)->value);
			free(((t_env *)new->content)->id);
			i = len + 2;
			len = ft_strlen(&str[i]);
			((t_env *)list->content)->value = ft_substr(str, i, len - 1);
			return (0);
		}
		list = list->next;
	}
	i = len + 2;
	len = ft_strlen(&str[i]);
	((t_env *)new->content)->value = ft_substr(str, i, len - 1);
	ft_lstadd_back(head, new);
	return (0);
}