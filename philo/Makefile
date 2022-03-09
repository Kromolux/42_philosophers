# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/05 09:02:13 by rkaufman          #+#    #+#              #
#    Updated: 2022/03/05 11:42:19 by rkaufman         ###   ########.fr        #
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

NAME				:=	philo

CC					:=	gcc
HEADERFILE			:=	philo.h

SRC			:=	ft_philosophers.c \
				ft_check_input.c \
				ft_error.c \
				ft_string_to_long.c \
				ft_get_arguments.c \
				ft_realloc.c \
				ft_copy.c \
				ft_write_string.c \
				ft_long_to_string.c \
				ft_strlen.c

OBJ			:=	$(SRC:%.c=%.o)

CFLAGS		:=	-Wall -Wextra -Werror

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