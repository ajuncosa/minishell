/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 11:34:27 by cruiz-de          #+#    #+#             */
/*   Updated: 2021/05/19 16:30:48 by ajuncosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**alloc_arg_array(t_data *data, t_cmd *com)
{
	char	**argv;
	int		i;
	int		j;

	argv = malloc((com->n_args + 2) * sizeof(char *));
	if (!argv)
		ft_exit(data, com);
	argv[0] = ft_strdup(com->cmd);
	if (!argv[0])
		ft_exit(data, com);
	i = 1;
	j = 0;
	while (j < com->n_args)
	{
		argv[i] = ft_strdup(com->args_str[j]);
		if (!argv[i])
			ft_exit(data, com);
		i++;
		j++;
	}
	argv[i] = NULL;
	return (argv);
}

int	fill_envp_item(t_env *lst_content, char **envp)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strdup(lst_content->id);
	if (!tmp1)
		return (0);
	*envp = ft_strjoin(tmp1, "=");
	if (!*envp)
		return (0);
	free(tmp1);
	tmp1 = ft_strdup(*envp);
	if (!tmp1)
		return (0);
	free(*envp);
	tmp2 = ft_strdup(lst_content->value);
	if (!tmp2)
		return (0);
	*envp = ft_strjoin(tmp1, tmp2);
	if (!*envp)
		return (0);
	free(tmp2);
	free(tmp1);
	return (1);
}

char	**create_envp_array(t_data *data)
{
	t_list	*lst;
	char	**envp;
	int		lst_size;
	int		i;

	lst_size = ft_lstsize(data->env_head);
	envp = malloc((lst_size + 1) * sizeof(char *));
	i = 0;
	lst = data->env_head;
	while (lst)
	{
		if (((t_env *)lst->content)->value)
		{
			if (!fill_envp_item((t_env *)lst->content, &envp[i]))
				return (NULL);
			i++;
		}
		lst = lst->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	exec_cmd(t_data *data, t_cmd *com, char **argv)
{
	char	*sterr;
	int		status;
	pid_t	pid;
	char	**envp;

	envp = create_envp_array(data);
	pid = fork();
	if (pid == 0)
	{
		if (execve(com->cmd, argv, envp) == -1)
		{
			dup2(data->std_out, STDOUT_FILENO);
			sterr = strerror(errno);
			error_msn(com->cmd, NULL, sterr);
		}
		exit(127);
	}
	else if (pid < 0)
	{
		sterr = strerror(errno);
		error_msn(NULL, NULL, sterr);
	}
	waitpid(pid, &status, 0);
	data->ret = WEXITSTATUS(status);
	free_envp_array(envp);
}

void	ft_cmd(t_cmd *com, t_data *data)
{
	char	*path;
	char	**argv;

	argv = alloc_arg_array(data, com);
	if (!ft_strchr(com->cmd, '/'))
	{
		path = ft_pathfinder(com->cmd, data);
		if (path == NULL)
		{
			dup2(data->std_out, STDOUT_FILENO);
			error_msn(com->cmd, NULL, "command not found");
			free_str_array(argv);
			data->ret = 127;
			return ;
		}
		free(com->cmd);
		com->cmd = path;
	}
	exec_cmd(data, com, argv);
	free_str_array(argv);
}
