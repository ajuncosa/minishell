GNL		= gnl/get_next_line.c
SRCS	= ${GNL} main.c exit.c utils.c parser.c var_env.c esc_utils.c esc_mngr.c redir_mngr.c redir_utils.c echo.c pwd.c export.c cd.c unset.c env.c exec.c exec_utils.c signals.c args.c args_cmd.c cmd_mngr.c start_shell.c
OBJS	= ${SRCS:.c=.o}
NAME	= minishell
CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Werror -Wextra
SANITIZE = -g -fsanitize=address
%.o: %.c
	${CC} -c $< -o $@

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
