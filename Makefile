# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: upopee <upopee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/28 11:42:57 by upopee            #+#    #+#              #
#*   Updated: 2017/04/04 19:46:04 by upopee           ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

# -- VARIABLES --

# Name
NAME = fdf

# Compiler
CC = gcc

# Flags
CFLAGS = -Wall -Werror -Wextra $(INCLUDES) -DDEBUG
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
FILES =		fdf \
			parse_input \

SOURCES = $(patsubst %,$(SRC_DIR)/%,$(FILES:=.c))
SRC_DIR = ./src
# Objects files
OBJECTS = $(patsubst %,$(OBJ_DIR)/%,$(FILES:=.o))
OBJ_DIR = ./obj

# -- RULES --

all: prep $(NAME)
	echo >> /dev/null

debug: lib
	printf "> \e[31;33;1m$(NAME)\e[0m \e[37;1m[\e[0m\e[34;1mDEBUG MODE\e[0m\e[37;1m]\e[0m : \e[32mCreating objects \e[0m "
	make obj
	printf "\n"
	printf "> \e[31;33;1m$(NAME)\e[0m \e[37;1m[\e[0m\e[34;1mDEBUG MODE\e[0m\e[37;1m]\e[0m : \e[32mCreating binary \e[0m "
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJECTS) -o $(NAME)
	printf "\t\t\e[37;1m[\e[32;1mDONE\e[0m\e[37;1m]\e[0m\n"

$(NAME): lib
	printf "> \e[31;33;1m$(NAME)\e[0m : \e[32mCreating objects \e[0m "
	make obj
	printf "\n"
	printf "> \e[31;33;1m$(NAME)\e[0m : \e[32mCreating binary\e[0m "
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJECTS) -o $(NAME)
	printf "\t\t\e[37;1m[\e[32;1mDONE\e[0m\e[37;1m]\e[0m\n"

obj: $(OBJECTS)
	echo >> /dev/null

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)
	printf "\e[32m.\e[0m"

lib:
	make -C $(LIB_DIR)

clean:
	printf "> \e[31;33;1m$(NAME)\e[0m : \e[31mDeleting objects\e[0m "
	rm -f $(OBJECTS)
	printf "\t\t\e[37;1m[\e[31;1mX\e[0m\e[37;1m]\e[0m\n"
	make -C $(LIB_DIR) $@

fclean: clean
	printf "> \e[31;33;1m$(NAME)\e[0m : \e[31mDeleting binary\e[0m "
	rm -f $(NAME)
	printf "\t\t\e[37;1m[\e[31;1mX\e[0m\e[37;1m]\e[0m\n"
	make -C $(LIB_DIR) $@

re: fclean all

prep:
	mkdir -p $(OBJ_DIR)

sandwich: re
	make clean
	echo "Sandwich ready !"
# This rule allow the library build process to complete even if there are
# files named 'all, clean, fclean, re' in the working directory


.PHONY: all obj lib clean fclean re sandwich prep debug

.SILENT: all obj lib clean fclean re sandwich prep debug $(NAME) $(OBJECTS)
