/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:06:51 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/05/04 13:47:18 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**paths_from_env(t_data *data)
{
	char		**paths;
	t_list		*lst;

	paths = NULL;
	lst = data->env_head;
	while (lst)
	{
		if (!ft_strcmp(((t_env *)lst->content)->id, "PATH"))
		{
			if (((t_env *)lst->content)->value)
			{
				paths = ft_split(((t_env *)lst->content)->value, ':');
				if (!paths)
					ft_exit(data, NULL);
			}
			break ;
		}
		lst = lst->next;
	}
	return (paths);
}

char	*is_in_path(char *path, char *cmd, t_data *data)
{
	char		*joined;
	char		*tmp;
	struct stat	stat;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		ft_exit(data, NULL);
	joined = ft_strjoin(tmp, cmd);
	if (!joined)
		ft_exit(data, NULL);
	free(tmp);
	lstat(joined, &stat);
	if (S_ISREG(stat.st_mode))
		return (joined);
	free(joined);
	return (NULL);
}

char	*ft_pathfinder(char *cmd, t_data *data)
{
	int		i;
	char	*valid_path;
	char	**paths;

	valid_path = NULL;
	paths = paths_from_env(data);
	if (paths)
	{
		i = 0;
		while (paths[i])
		{
			valid_path = is_in_path(paths[i], cmd, data);
			if (valid_path)
				break ;
			i++;
		}
		free_str_array(paths);
	}
	return (valid_path);
}
