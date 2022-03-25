# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/17 11:30:26 by rkaufman          #+#    #+#              #
#    Updated: 2022/03/21 10:27:18 by rkaufman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	philo

CC			:=	gcc
HEADERFILE	:=	philo.h

SRC			:=	ft_philosophers.c \
				ft_check_input.c \
				ft_error.c \
				ft_get_arguments.c \
				ft_init_philos.c \
				ft_status.c \
				ft_philo_thread.c \
				ft_philo_thread1.c \
				ft_utils.c \
				ft_string_utils.c

OBJ			:=	$(SRC:%.c=%.o)

CFLAGS		:=	-Wall -Wextra -Werror -lpthread #-g -pthread -fsanitize=thread

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lpthread -o $(NAME)

#%.o: %.c
#	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader $(SRC) $(HEADERFILE)

git:
	git add *

.PHONY: clean fclean re