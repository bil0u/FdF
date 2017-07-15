# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: upopee <upopee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/28 11:42:57 by upopee            #+#    #+#              #
#    Updated: 2017/07/10 04:13:50 by upopee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -- VARIABLES --

# Name
NAME = fdf

# Compiler
CC = gcc

# Flags
CFLAGS = -Wall -Wextra -Wall $(INCLUDES) -g -O0
LFLAGS = -framework OpenGL -framework AppKit -lmlx -L $(MLX_DIR) -lft -L $(LIB_DIR) -lgraphic -L $(LIB_GRAPHIC_DIR) -lpthread
# Library paths
MLX_DIR = ./minilibx

LIB_DIR = ./libft
LIB_INCLUDES_DIR = $(LIB_DIR)/inc

LIB_GRAPHIC_DIR = ./libgraphic
LIB_GRAPHIC_INCLUDES_DIR = $(LIB_GRAPHIC_DIR)/inc
# Sources paths
VPATH = ./src
INCLUDES_DIR = ./inc

# Includes paths
INCLUDES = -I $(INCLUDES_DIR) -I $(LIB_INCLUDES_DIR) -I $(LIB_GRAPHIC_INCLUDES_DIR)

# Sources files
FILES =		main_fdf \
			hook_mlx \
			hook_utils \
			parse_input \
			parse_utils \
			env_utils \
			draw_utils \
			color_init \
			color_utils \
			help_utils \
			help_texts \
			debug_utils \
			world_utils \
			window_utils \
			clear_frame \
			fastline_fdf \

SOURCES = $(patsubst %,$(SRC_DIR)/%,$(FILES:=.c))
SRC_DIR = ./src

# Objects files
OBJECTS = $(patsubst %,$(OBJ_DIR)/%,$(FILES:=.o))
OBJ_DIR = ./.obj

# -- RULES --

all: prep $(NAME)

$(NAME): lib
	printf "> \e[31;33;1m$(NAME)\e[0m : \e[32mCreating objects \e[0m "
	make obj
	printf "\n"
	printf "> \e[31;33;1m$(NAME)\e[0m : \e[32mCreating binary\e[0m "
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJECTS) -o $(NAME)
	printf "\t\t\e[37;1m[\e[32;1mDONE\e[0m\e[37;1m]\e[0m\n"

obj: $(OBJECTS)
	echo >> /dev/null

$(OBJ_DIR)/%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
	printf "\e[32m.\e[0m"

lib:
	make -C $(LIB_DIR)
	make -C $(LIB_GRAPHIC_DIR)

clean:
	printf "> \e[31;33;1m$(NAME)\e[0m : \e[31mDeleting objects\e[0m "
	rm -rf $(OBJ_DIR)
	printf "\t\t\e[37;1m[\e[31;1mX\e[0m\e[37;1m]\e[0m\n"
	make -C $(LIB_DIR) $@
	make -C $(LIB_GRAPHIC_DIR) $@

fclean: clean
	printf "> \e[31;33;1m$(NAME)\e[0m : \e[31mDeleting binary\e[0m "
	rm -f $(NAME)
	printf "\t\t\e[37;1m[\e[31;1mX\e[0m\e[37;1m]\e[0m\n"
	make -C $(LIB_DIR) $@
	make -C $(LIB_GRAPHIC_DIR) $@

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
