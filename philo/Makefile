# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/03 23:18:02 by juzoanya          #+#    #+#              #
#    Updated: 2022/10/10 22:35:05 by juzoanya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -ggdb3 $(INC) #-fsanitize=address -g

PATH_SRC = ./src/
PATH_INC = ./inc/
PATH_OBJS = ./objs/
INC = -I ./inc

SRC = 	$(PATH_SRC)main.c \
		$(PATH_SRC)errors.c \
		$(PATH_SRC)tasks.c \
		$(PATH_SRC)init.c \
		$(PATH_SRC)routine.c \
		$(PATH_SRC)utils.c \
		$(PATH_SRC)libft_utils.c \


OBJS = $(patsubst $(PATH_SRC)%.c, $(PATH_OBJS)%.o, $(SRC))

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(SRC) -o $(NAME) $(CFLAGS)
	@echo "$(NAME) created"

$(PATH_OBJS)%.o:	$(PATH_SRC)%.c
	@mkdir -p $(PATH_OBJS)
	$(CC) $(CFLAGS) $(INC). -c $< -o $@

clean:
	@rm -rf $(PATH_OBJS)
	@echo "OBJ Deleted!"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(NAME) is Deleted!"

re:	fclean all

.PHONY:	all clean fclean re
