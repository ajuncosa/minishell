GNL		= gnl/get_next_line.c
SRCS	= ${GNL} main.c echo.c env.c exit.c parser.c pwd.c export.c unset.c cd.c ls.c exit_status.c
OBJS	= ${SRCS:.c=.o}
NAME	= minishell
CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Werror -Wextra
SANITIZE = -g -fsanitize=address
%.o: %.c
	${CC} -c $< -o $@

${NAME}:	${OBJS}
				make -C ft_printf/
				$(CC) -L ft_printf/ -lftprintf $^ -o ${NAME}

all:		${NAME}

clean:
				${RM} ${OBJS}
				make clean -C ft_printf/

fclean:		clean
				${RM} ${NAME}
				make fclean -C ft_printf/

re:			fclean all

.PHONY:		all clean fclean re
