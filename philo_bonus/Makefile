# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/05 09:02:13 by rkaufman          #+#    #+#              #
#    Updated: 2022/03/13 10:55:27 by rkaufman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/17 11:30:26 by rkaufman          #+#    #+#              #
#    Updated: 2022/03/03 13:26:48 by rkaufman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	philo_bonus

CC			:=	gcc
HEADERFILE	:=	philo_bonus.h

SRC			:=	ft_philosophers_bonus.c \
				ft_check_input_bonus.c \
				ft_error_bonus.c \
				ft_string_to_long_bonus.c \
				ft_get_arguments_bonus.c \
				ft_realloc_bonus.c \
				ft_copy_bonus.c \
				ft_write_string_bonus.c \
				ft_long_to_string_bonus.c \
				ft_strlen_bonus.c \
				ft_time_bonus.c \
				ft_init_process_bonus.c \
				ft_status_bonus.c \
				ft_philo_process_bonus.c \
				ft_check_meals_bonus.c

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

norminette:
	norminette -R CheckForbiddenSourceHeader $(SRC) $(HEADERFILE)

git:
	git add *

.PHONY: clean fclean re