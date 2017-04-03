# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: upopee <upopee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/28 11:42:57 by upopee            #+#    #+#              #
#*   Updated: 2017/04/04 01:50:16 by upopee           ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

# -- VARIABLES --

# Name
NAME = fdf

# Compiler
CC = gcc

# Flags
CFLAGS = -Wall -Werror -Wextra $(INCLUDES)
LFLAGS = -lmlx -framework OpenGL -framework AppKit -lft -L $(LIB_DIR)

# Library paths
LIB_DIR = ./libft
LIB_INCLUDES_DIR = $(LIB_DIR)/includes

# Sources paths
VPATH = ./src
INCLUDES_DIR = ./includes

# Includes paths
INCLUDES = -I $(INCLUDES_DIR) -I $(LIB_INCLUDES_DIR)

# Sources files
SOURCES =	fdf.c \
			parse_input.c \

# Objects files
OBJECTS = $(SOURCES:.c=.o)

# -- RULES --

all: $(NAME)
	echo >> /dev/null

$(NAME): lib
	printf "> \033[31;33;1m$(NAME)\033[0m : \033[32mCreating objects \033[0m "
	make obj
	printf "\n"
	printf "> \033[31;33;1m$(NAME)\033[0m : \033[32mCreating binary\033[0m "
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJECTS) -o $(NAME)
	printf "\t\t\033[37;1m[\033[32;1mDONE\033[0m\033[37;1m]\033[0m\n"

obj: $(OBJECTS)
	echo >> /dev/null

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
	printf "\033[32m.\033[0m"

lib:
	make -C $(LIB_DIR)

clean:
	printf "> \033[31;33;1m$(NAME)\033[0m : \033[31mDeleting objects\033[0m "
	rm -f $(OBJECTS)
	printf "\t\t\033[37;1m[\033[31;1mX\033[0m\033[37;1m]\033[0m\n"
	make -C $(LIB_DIR) $@

fclean: clean
	printf "> \033[31;33;1m$(NAME)\033[0m : \033[31mDeleting binary\033[0m "
	rm -f $(NAME)
	printf "\t\t\033[37;1m[\033[31;1mX\033[0m\033[37;1m]\033[0m\n"
	make -C $(LIB_DIR) $@

re: fclean all

sandwich: re
	make clean
	echo "Sandwich ready !"
# This rule allow the library build process to complete even if there are
# files named 'all, clean, fclean, re' in the working directory


.PHONY: all obj lib clean fclean re sandwich

.SILENT: all obj lib clean fclean re sandwich $(NAME) $(OBJECTS)
