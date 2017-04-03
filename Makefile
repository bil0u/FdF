# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: upopee <upopee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/28 11:42:57 by upopee            #+#    #+#              #
#*   Updated: 2017/04/03 19:57:38 by upopee           ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

# -- VARIABLES --

# Names
NAME = fdf

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -c -Wall -Werror -Wextra

# Files path
INC = inc/

# Files path
VPATH = src/


SRCS =	parse_input.c \

# -- OBJECTS --

OBJS = $(SRCS:.c=.o)

# -- RULES --

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME)
	@echo "Library created ! [OK]"

%.o: %.c
	@$(CC) $(CFLAGS) -I $(INC) -o $@ $^

clean:
	@rm -f $(OBJS)
	@echo "Objects deleted   [OK]"

fclean: clean
	@rm -f $(NAME)
	@echo "Binary deleted    [OK]"

re: fclean all

# This rule allow the library build process to complete even if there are
# files named 'all, clean, fclean, re' in the working directory

.PHONY: all clean fclean re
