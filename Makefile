# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: upopee <upopee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/28 11:42:57 by upopee            #+#    #+#              #
#*   Updated: 2017/04/03 21:13:25 by upopee           ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc

CFLAGS = -Wall -Werror -Wextra -I $(INC) -I $(LIB_INC)
LFLAGS = -lmlx -framework OpenGL -framework AppKit -lft -L$(LIB_PATH)

LIB_PATH = libft
LIB_INC = $(LIB_PATH)/includes

VPATH = src
INC = inc

SRCS =	fdf.c \
		parse_input.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): libft $(OBJS)
	@$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) -o $(NAME)
	@echo "-- $(NAME): binary created --"

%.o: %.c
	@$(CC) $(CFLAGS) -c $^

libft:
	@make -C $(LIB_PATH)

clean:
	@rm -f $(OBJS)
	@make -C $(LIB_PATH) $@
	@echo "-- $(NAME): objects deleted --"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB_PATH) $@
	@echo "-- $(NAME): binary deleted --"

re: fclean all

# This rule allow the library build process to complete even if there are
# files named 'all, clean, fclean, re' in the working directory

.PHONY: all clean fclean re libft
