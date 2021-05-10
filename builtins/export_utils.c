/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 12:21:59 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/05/10 12:05:27 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fill_node(t_env *new_content, t_env *lst_content)
{
	new_content->id = ft_strdup(lst_content->id);
	if (!new_content->id)
		return (0);
	if (lst_content->value)
	{
		new_content->value = ft_strdup(lst_content->value);
		if (!new_content->value)
			return (0);
	}
	else
		new_content->value = NULL;
	return (1);
}

int	copy_list(t_list **sorted, t_list *env_head)
{
	t_list	*lst;
	t_list	*new;
	t_env	*env;

	lst = env_head;
	while (lst)
	{
		env = malloc(sizeof(t_env));
		if (!env)
			return (0);
		new = ft_lstnew(env);
		if (!new)
			return (0);
		if (!fill_node(env, (t_env *)lst->content))
			return (0);
		ft_lstadd_back(sorted, new);
		lst = lst->next;
	}
	return (1);
}

void	sort_alphabetically(t_list **sorted)
{
	t_list	*lst;
	t_list	*biggest;
	t_env	*tmp;
	int		swapped;

	swapped = 1;
	biggest = NULL;
	while (swapped)
	{
		swapped = 0;
		lst = *sorted;
		while (lst->next != biggest)
		{
			if (ft_strcmp(((t_env *)lst->content)->id,
					((t_env *)(lst->next)->content)->id) > 0)
			{
				tmp = lst->content;
				lst->content = (lst->next)->content;
				(lst->next)->content = tmp;
				swapped = 1;
			}
			lst = lst->next;
		}
		biggest = lst;
	}
}

void	print_export_list(t_data *data, t_cmd *com)
{
	t_list	*list;
	t_list	*sorted;

	sorted = NULL;
	if (!copy_list(&sorted, data->env_head))
		ft_exit(data, com);
	sort_alphabetically(&sorted);
	list = sorted;
	while (list)
	{
		if (((t_env *)list->content)->value)
			printf("declare -x %s=\"%s\"\n", ((t_env *)list->content)->id,
				((t_env *)list->content)->value);
		else
			printf("declare -x %s\n", ((t_env *)list->content)->id);
		list = list->next;
	}
	ft_lstclear(&sorted, del_lst);
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
