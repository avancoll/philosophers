# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 14:13:45 by avancoll          #+#    #+#              #
#    Updated: 2023/05/25 12:35:18 by avancoll         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS =	action.c\
		error.c\
		init.c\
		philo.c\
		utils.c\

OBJS		= $(SRCS:.c=.o)

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -fsanitize=thread -g

THREAD = -lpthread

RM			= rm -f

$(NAME):	$(OBJS)
			$(CC) ${CFLAGS} -o $(NAME) $(OBJS) $(THREAD)

all:	$(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re