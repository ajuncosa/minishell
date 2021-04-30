/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:14:49 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/04/30 12:31:43 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_new_env(t_data *data, t_cmd *com, char *id, char **value)
{
	t_list	*new;
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (0);
	new = ft_lstnew(env);
	if (!new)
		return (0);
	env->id = ft_strdup(id);
	if (!env->id)
		return (0);
	if (value)
		env->value = *value;
	else
		env->value = NULL;
	ft_lstadd_back(&data->env_head, new);
	return (1);
}

void	no_equal_sign(t_data *data, t_cmd *com, char *arg)
{
	t_list	*list;
	int		flag;

	flag = 0;
	list = data->env_head;
	while (list)
	{
		if (!ft_strcmp(((t_env *)list->content)->id, arg))
		{
			flag = 1;
			break ;
		}
		list = list->next;
	}
	if (!flag)
		if (!create_new_env(data, com, arg, NULL))
			ft_exit(data, com);
}

int	separate_id_value(char *arg, char **id, char **value)
{
	int		len_id;
	int		len_v;

	len_id = 0;
	while (arg[len_id] != '=')
		len_id++;
	len_v = ft_strlen(&arg[len_id + 1]);
	*id = ft_substr(arg, 0, len_id);
	if (!*id)
		return (0);
	*value = ft_substr(arg, len_id + 1, len_v);
	if (!*value)
		return (0);
	return (1);
}

void	yes_equal_sign(t_data *data, t_cmd *com, char *arg)
{
	char	*id;
	char	*value;
	int		flag;
	t_list	*list;

	flag = 0;
	if (!separate_id_value(arg, &id, &value))
		ft_exit(data, com);
	list = data->env_head;
	while (list)
	{
		if (!ft_strcmp(((t_env *)list->content)->id, id))
		{
			free(((t_env *)list->content)->value);
			((t_env *)list->content)->value = value;
			flag = 1;
			break ;
		}
		list = list->next;
	}
	if (!flag)
		if (!create_new_env(data, com, id, &value))
			ft_exit(data, com);
	free(id);
}

void	ft_export(t_data *data, t_cmd *com)
{
	int		i;

	data->ret = 0;
	if (com->args_str == NULL)
	{
		print_export_list(data);
		return ;
	}
	i = 0;
	while (i < com->n_args)
	{
		if (!export_errors(com->args_str[i]))
		{
			i++;
			data->ret = 1;
			continue ;
		}
		if (!ft_strchr(com->args_str[i], '='))
			no_equal_sign(data, com, com->args_str[i]);
		else
			yes_equal_sign(data, com, com->args_str[i]);
		i++;
	}
}
