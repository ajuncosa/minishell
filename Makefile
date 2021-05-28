GNL		= gnl/get_next_line.c
PARSER	= parser/args_cmd.c parser/args.c parser/esc_mngr.c parser/esc_utils_libft.c parser/esc_utils.c parser/parser_utils.c parser/parser.c parser/syntax_errors.c parser/var_env.c
BUILTINS = builtins/exit.c builtins/cd.c builtins/echo.c builtins/env.c builtins/export_utils.c builtins/export.c builtins/pwd.c builtins/unset.c
EXECUTE	= execute/cmd_mngr.c execute/exec_utils.c execute/exec.c execute/redir_array.c execute/redir_mngr.c execute/redir_utils.c execute/pipes.c
SRCS	= ${GNL} ${PARSER} ${BUILTINS} ${EXECUTE} main.c utils.c utils_errors.c signals.c start_shell.c
OBJS	= ${SRCS:.c=.o}
NAME	= minishell
CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Werror -Wextra
SANITIZE = -g -fsanitize=address

${NAME}:	${OBJS}
				make bonus -C libft/
				cp libft/libft.a ${NAME}
				${CC} -L libft/ -lft $^ -o ${NAME}

all:		${NAME}

clean:
				${RM} ${OBJS}
				make clean -C libft/

fclean:		clean
				${RM} ${NAME}
				make fclean -C libft/

re:			fclean all

.PHONY:		all clean fclean re
