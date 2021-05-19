SRCS	= ft_strlen.c ft_strncmp.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_atoi.c ft_strchr.c ft_strdup.c ft_substr.c ft_strjoin.c ft_split.c ft_itoa.c ft_strcmp.c
SRCS_B	= ft_lstnew_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstsize_bonus.c
OBJS	= ${SRCS:.c=.o}
OBJS_B	= ${SRCS_B:.c=.o}
NAME	= libft.a
CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Werror -Wextra
.c.o:
		${CC} ${FLAGS} -c $< -o ${<:.c=.o}
${NAME}:	${OBJS}
			ar rc  ${NAME} ${OBJS}
			ranlib ${NAME}
bonus:		${OBJS} ${OBJS_B}
			ar rc ${NAME} ${OBJS} ${OBJS_B}
			ranlib ${NAME}
all:		${NAME}
clean:
			${RM} ${OBJS} ${OBJS_B}
fclean:		clean
			${RM} ${NAME}
re:			fclean bonus
.PHONY:		bonus all clean fclean re
