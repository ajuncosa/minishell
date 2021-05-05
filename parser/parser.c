/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:53:05 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/05/05 12:12:27 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	transform_line(char *str, t_data *data)
{
	int			len;

	len = esc_size(str);
	if (len == -1)
	{
		data->ret = 0;
		return (0);
	}
	data->line = line_to_struct(str, len);
	if (!data->line)
		ft_exit(data, NULL);
	if (!dollar_finder(&data->env_head, &data->line, data->ret))
		return (0);
	if (!syntax_errors(data->line))
	{
		free(data->line);
		data->ret = 258;
		return (0);
	}
	return (1);
}

void	parser_loop(t_data *data)
{
	t_list		*new;
	t_cmd		*com;
	int			i;
	int			r;

	i = 0;
	com = NULL;
	while (data->line[i].c != '\0')
	{
		parser_alloc_init(data, &com, &new);
		while (data->line[i].c == ' ' && !data->line[i].esc)
			i++;
		i = find_arg_seps(data, com, i, 0);
		while (data->line[i].c == ' ' && !data->line[i].esc)
			i++;
		r = countalloc_args(com, data, new, &data->line[i]);
		if (r == -1)
			return ;
		else if (r == 0)
			continue ;
		save_cmd_args(data, com, &i);
		i = find_arg_seps(data, com, i, 1);
		ft_lstadd_back(&data->cmd_head, new);
	}
}

void	parser(t_data *data, char *str)
{
	signal(SIGINT, signals_son);
	signal(SIGQUIT, signals_son);
	data->cmd_head = NULL;
	if (!transform_line(str, data))
		return ;
	parser_loop(data);
	cmd_manager(data);
	free(data->line);
	data->line = NULL;
	ft_lstclear(&data->cmd_head, &del_lst_cmd);
}
