/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 12:21:59 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/04/30 12:32:53 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_list(t_data *data)
{
	t_list	*list;

	list = data->env_head;
	while (list)
	{
		if (((t_env *)list->content)->value)
			printf("declare -x %s=\"%s\"\n", ((t_env *)list->content)->id,
				((t_env *)list->content)->value);
		else
			printf("declare -x %s\n", ((t_env *)list->content)->id);
		list = list->next;
	}
	data->ret = 0;
}

int	export_errors(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			error_msn("export", str, "not a valid identifier");
			return (0);
		}
		i++;
	}
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		error_msn("export", str, "not a valid identifier");
		return (0);
	}
	return (1);
}
