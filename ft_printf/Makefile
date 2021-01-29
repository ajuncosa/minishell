SRCS	= ft_printf.c printf_utils.c printf_c.c printf_s.c printf_d.c printf_p.c printf_x_lower.c printf_x_upper.c printf_u.c printf_format.c

SRCS_B	= ft_printf_bonus.c printf_c_bonus.c printf_d_bonus.c printf_p_bonus.c printf_s_bonus.c printf_u_bonus.c printf_x_lower_bonus.c printf_x_upper_bonus.c printf_format_bonus.c printf_utils_bonus.c printf_n_bonus.c

OBJS	= ${SRCS:.c=.o}

OBJS_B	= ${SRCS_B:.c=.o}

NAME	= libftprintf.a

CC		= cc

RM		= rm -f

CFLAGS	= -Wall -Werror -Wextra 
.c.o:
		${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			make bonus -C ../libft/
			cp ../libft/libft.a ${NAME}
			ar rc ${NAME} ${OBJS}
			ranlib ${NAME}

bonus:		${OBJS_B}
			make bonus -C ../libft/
			cp ../libft/libft.a ${NAME}
			ar rc ${NAME} ${OBJS_B}
			ranlib ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS} ${OBJS_B}
			make clean -C ../libft/

fclean:		clean
			${RM} ${NAME}
			make fclean -C ../libft/

re:			fclean all

.PHONY:		bonus all clean fclean re
