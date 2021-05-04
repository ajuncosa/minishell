/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuncosa <ajuncosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:36:50 by ajuncosa          #+#    #+#             */
/*   Updated: 2021/05/04 13:29:25 by ajuncosa         ###   ########.fr       */
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
# include <sys/types.h>
# include "gnl/get_next_line.h"
# include "libft/libft.h"

typedef struct s_env
{
	char	*id;
	char	*value;
}			t_env;

typedef struct s_letter
{
	char	c;
	int		esc;
}				t_letter;

typedef struct s_cmd
{
	char		*cmd;
	char		**args_str;
	t_letter	**args;
	char		sep_0;
	char		sep_1;
	int			n_args;
	int			n_redir;
}			t_cmd;

typedef struct s_redir
{
	char	*type;
	char	*file;
}			t_redir;

typedef struct s_data
{
	char		**envp;
	t_list		*env_head;
	t_list		*cmd_head;
	t_letter	*line;
	int			ret;
	int			std_in;
	int			std_out;
}				t_data;

char	*g_user;
pid_t	g_pid;

/* Main Functions */
void		header(void);
void		lst_env(t_data *data);
void		set_user(t_data *data);
void		del_oldpwd(t_data *data);
void		prompt(void);
/* Signals */
void		quit(int sig);
void		ctrl_c(int sig);
void		ctrl_d(int ctrl, char **str, t_data *data);
/* Parser */
void		parser(t_data *data, char *str);
int			syntax_errors(t_letter *str);
void		parser_alloc_init(t_data *data, t_cmd **com, t_list **new);
int			countalloc_args(t_cmd *com, t_data *data, t_list *new,
				t_letter *line);
int			count_args(t_letter *str);
void		save_cmd_args(t_data *data, t_cmd *com, int *i);
t_letter	*quote_hunter(t_letter *str);
int			save_args(t_letter **str, t_cmd *com, int *start);
int			find_cmd(t_cmd *com);
int			find_arg_seps(t_data *data, t_cmd *com, int i, int sep);
/* Commands */
void		cmd_manager(t_data *data);
int			create_args_str(t_cmd *com);
void		cmd_caller(t_cmd *com, t_data *data);
void		ft_echo(t_data *data, t_cmd *com);
void		ft_env(t_data *data, char **args);
void		ft_pwd(t_data *data, char **args);
void		ft_export(t_data *data, t_cmd *com);
void		print_export_list(t_data *data);
int			export_errors(char *str);
void		ft_unset(t_data *data, t_cmd *com);
void		ft_cd(t_data *data, t_cmd *com);
void		ft_cmd(t_cmd *com, t_data *data);
char		*ft_pathfinder(char *cmd, t_data *data);
/* Exit */
void		ft_exit(t_data *data, t_cmd *com);
void		del_lst(void *env);
void		del_lst_cmd(void *cmd);
/* Redirections and Dollars */
int			check_if_redir(t_cmd *com);
void		count_redir(t_cmd *com);
int			arg_cleaner(t_cmd *com, t_redir *redir);
void		redir_manager(t_cmd *com, t_data *data);
int			redir_open_files(t_data *data, t_redir redir, int *last, int i);
void		redir_open_error(t_data *data, t_redir *redir, int i, int n_redir);
int			dollar_finder(t_list **env_head, t_letter **str, int ret);
/* Misc utils */
char		*is_in_env(t_list **env_head, char *str);
int			is_space_quote_redir_or_endofcmd(t_letter c);
int			is_space_redir_or_endofcmd(t_letter c);
void		error_msn(char *cmd, char *str, char *txt);
void		free_str_array(char **argv);
void		fork_errors(void);
/* Escapes utils and struct */
int			esc_size(char *str);
t_letter	*line_to_struct(char *str, int len);
char		*struct_to_str(t_letter *struc, int start, int len);
t_letter	*str_to_struct(char *str);
t_letter	*esc_substr(t_letter *str, unsigned int start, size_t len);
t_letter	*esc_join(t_letter *s1, t_letter *s2);
int			esc_strlen(t_letter *str);
t_letter	*esc_dup(t_letter *str);
int			esc_cmp(t_letter *s1, char *s2);
int			is_escapable(char c, int quote);

#endif
