/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:36:50 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/03/18 18:17:21 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/stat.h>
//# include <sys/types.h>
# include "gnl/get_next_line.h"
# include "libft/libft.h"

typedef struct s_env
{
	char	*id;
	char	*value;
}			t_env;

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	char	sep_0;
	char	sep_1;
	int		n_args;
	int		n_redir;
}			t_cmd;

typedef struct s_redir
{
	char	*type;
	char	*file;
}			t_redir;

int		ft_echo(t_cmd *com);
int		ft_env(t_list **head, char **args);
void	ft_exit(t_list **env_head, t_list **cmd_head, char *user);
void	del_lst(void *env);
void	del_lst_cmd(void *cmd);
int		parser(char *str, t_list **env_head, int ret, char *user);
int		cmd_caller(t_cmd *com, t_list **env_head, t_list **cmd_head, int ret, char *user);
int		ft_pwd(char **args);
int		ft_export(t_list **head, t_cmd *com);
int		ft_unset(t_list **head, t_cmd *com);
int		ft_cd(t_cmd *com, char *user, t_list **env_head);
int		ft_exit_status(int ret);
int 	ft_cmd(t_cmd *com, t_list **env_head);
int		check_if_redir(t_cmd *com);
int		redir_manager(t_cmd *com, t_list **env_head, t_list **cmd_head, int ret, char *user);


#endif
