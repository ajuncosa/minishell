/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:11:43 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/05/04 13:27:23 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_redir(t_cmd *com)
{
	int		i;
	char	*arg;

	i = 0;
	while (i < com->n_args)
	{
		arg = struct_to_str(com->args[i], 0, esc_strlen(com->args[i]));
		if ((!ft_strcmp(arg, ">") || !ft_strcmp(arg, ">>")
				|| !ft_strcmp(arg, "<")) && !com->args[i][0].esc)
		{
			free(arg);
			return (1);
		}
		free(arg);
		i++;
	}
	return (0);
}

void	count_redir(t_cmd *com)
{
	int		i;
	char	*arg;

	i = 0;
	com->n_redir = 0;
	while (i < com->n_args)
	{
		arg = struct_to_str(com->args[i], 0, esc_strlen(com->args[i]));
		if ((!ft_strcmp(arg, ">") || !ft_strcmp(arg, ">>")
				|| !ft_strcmp(arg, "<")) && !com->args[i][0].esc)
			com->n_redir++;
		free(arg);
		i++;
	}
}

void	redir_open_error(t_data *data, t_redir *redir, int i, int n_redir)
{
	char	*sterr;

	sterr = strerror(errno);
	error_msn(redir[i].file, NULL, sterr);
	i = 0;
	while (i < n_redir)
	{
		free(redir[i].type);
		free(redir[i].file);
		i++;
	}
	free(redir);
	data->ret = 1;
}

int	redir_open_files(t_data *data, t_redir redir, int *last, int i)
{
	int	fd;

	if (!ft_strcmp(redir.type, ">"))
	{
		last[1] = i;
		fd = open(redir.file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	}
	else if (!ft_strcmp(redir.type, ">>"))
	{
		last[1] = i;
		fd = open(redir.file, O_WRONLY | O_APPEND | O_CREAT, 0777);
	}
	else if (!ft_strcmp(redir.type, "<"))
	{
		last[0] = i;
		fd = open(redir.file, O_RDONLY);
	}
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}
