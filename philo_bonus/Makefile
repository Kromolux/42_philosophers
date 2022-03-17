# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/05 09:04:12 by rkaufman          #+#    #+#              #
#    Updated: 2022/03/17 18:27:27 by rkaufman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	philo_bonus

CC			:=	gcc
HEADERFILE	:=	philo_bonus.h

SRC			:=	ft_philosophers_bonus.c \
				ft_check_input_bonus.c \
				ft_error_bonus.c \
				ft_get_arguments_bonus.c \
				ft_init_process_bonus.c \
				ft_status_bonus.c \
				ft_philo_process_bonus.c \
				ft_philo_process_utils_bonus.c \
				ft_check_meals_bonus.c \
				ft_utils_bonus.c \
				ft_string_utils_bonus.c \
				ft_semaphore.c

OBJ			:=	$(SRC:%.c=%.o)

CFLAGS		:=	-Wall -Wextra -Werror -g -pthread -fsanitize=thread

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lpthread -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


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