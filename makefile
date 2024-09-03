# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/24 13:47:11 by fgrabows          #+#    #+#              #
#    Updated: 2024/09/03 17:53:27 by fgrabows         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
C_FILES = main.c free_fun.c file_readers.c input_checkers.c utils.c bonus/utils_bonus.c
O_FILES = $(C_FILES:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(O_FILES) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(O_FILES) $(LIBFT)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@	
	
$(LIBFT):
	make -C libft
	
clean:
	rm -rf $(O_FILES)
	make clean -C libft
	
fclean: clean
	make fclean -C libft
	rm -rf $(NAME)
	

re: fclean all
	make re -C libft
	
.PHONY: all clean fclean re