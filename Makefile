SRCS	= main.c cmd_exec.c ft_split.c get_cmd_path.c  pipex_utils.c pipex_utils2.c
HEADER  = pipex.h
OBJS	= ${SRCS:.c=.o}

NAME	= pipex

CC	= cc

RM	= rm -f

CFLAGS = -Wall -Werror -Wextra

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}  :${OBJS} ${HEADER}
		  ${CC} ${SRCS} -o ${NAME} ${CFLAGS} 
all:	${NAME}

clean:
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

.PHONY:		all clean fclean re
