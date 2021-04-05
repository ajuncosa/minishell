/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:36:50 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/04/05 13:03:25 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
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

typedef struct s_data
{
	t_list	*env_head;
	t_list	*cmd_head;
	//char	*user;
	int		ret;
}				t_data;


char 	*user;
pid_t	pid;

int		ft_echo(t_cmd *com);
int		ft_env(t_data data, char **args);
int		ft_exit(t_data data, t_cmd *com);
void	del_lst(void *env);
void	del_lst_cmd(void *cmd);
int		parser(t_data data, char *str, char **envp);
int		cmd_caller(t_cmd *com, t_data data, char **envp);
int		ft_pwd(char **args);
int		ft_export(t_data data, t_cmd *com);
int		ft_unset(t_data data, t_cmd *com);
int		ft_cd(t_data data, t_cmd *com);
int 	ft_cmd(t_cmd *com, char **envp, t_data data);
int		check_if_redir(t_cmd *com);
int		redir_manager(t_cmd *com, t_data data, char **envp);
int		dollar_finder(t_list **env_head, char **str, int ret);
char	*is_in_env(t_list **env_head, char *str);
int		is_space_quote_redir_or_endofcmd(char c);
int		is_space_redir_or_endofcmd(char c);
int		filter_empty_args(t_cmd *com);

#endif
