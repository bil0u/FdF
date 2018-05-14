# -- PROJECT VARIABLES & COMMANDS --

NAME =		fdf
CC =		gcc
CFLAGS =	-Wall -Werror -Wextra
CPPFLAGS =	-I $(INC_DIR) -I $(LIBFT_DIR) -I $(LIBGR_DIR)
DEPFLAGS =	-MMD

SHELL =		/bin/bash
LDMAKE =	make -C
MKDIR =		mkdir -p
RMDIR =		rm -rf
RM =		rm -f
NORM =		norminette

# -- LIBRARIES --

LDLIBS =	-lft -lgraphic -lpthread -framework OpenGL -framework AppKit
LDFLAGS =	-L $(LIBFT_DIR) -L $(LIBGR_DIR)

LIBFT_DIR =	libft
LIBFT_LIB =	$(LIBFT_DIR)/libft.a

LIBGR_DIR =	libgraphic
LIBGR_LIB =	$(LIBGR_DIR)/libgraphic.a

# -- PATHS NAMES --

SRC_DIR =	sources
INC_DIR =	includes
OBJ_DIR =	.objects

# -- PROJECT FILES --

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

OBJECTS = $(patsubst %,$(OBJ_DIR)/%,$(FILES:=.o))

# -- IMPLICIT RULES  / LINKING --

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile
	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(NB)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(eval TO_DO=$(shell echo $$((20-$(INDEX)*20/$(NB) - 1))))
	@$(eval COLOR=$(shell list=(160 196 202 208 215 221 226 227 190 154 118 82 46); index=$$(($(PERCENT) * $${#list[@]} / 100)); echo "$${list[$$index]}"))
	@printf "\r> $(YELLOW)$(NAME)$(EOC) : Building objects...    %2d%% $(CNO)[`printf '#%.0s' {0..$(DONE)}`%*s]$(YELLOW)%*.*s%s$(EOC)$(ERASELN)" $(PERCENT) $(COLOR) $(TO_DO) "" $(DELTA) $(DELTA) "$(shell echo "$@" | sed 's/^.*\///')"
	@$(CC) -c $< -o $@ $(CFLAGS) $(CPPFLAGS) $(DEPFLAGS)
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

# -- RULES --

all: $(LIBFT_LIB) $(LIBGR_LIB)
	@$(MAKE) -j $(NAME)

$(NAME): $(LIBFT_LIB) $(LIBGR_LIB) $(OBJ_DIR) $(OBJECTS)
	@$(CC) $(LDLIBS) $(LDFLAGS) $(OBJECTS) -o $@
	@printf "\r$(ERASELN)$(GREEN_B)✓$(EOC) $(YELLOW)$(NAME)$(EOC) : Binary created\n"

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

$(LIBGR_LIB):
	@$(MAKE) -C $(LIBGR_DIR)

$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)

clean: libclean
	@if [ -e $(OBJ_DIR) ]; \
	then \
		$(RMDIR) $(OBJ_DIR); \
		printf "$(RED_B)✗$(EOC) $(YELLOW)$(NAME)$(EOC) : Objects deleted\n"; \
	fi;

fclean: clean libfclean
	@if [ -e $(NAME) ]; \
	then \
		$(RM) $(NAME); \
		printf "$(RED_B)✗$(EOC) $(YELLOW)$(NAME)$(EOC) : Binary deleted\n"; \
	fi;

re: fclean all

norm:
	@$(NORM) $(SRC_DIR)
	@$(NORM) $(INC_DIR)

lib:
	@$(MAKE) $(LIBFT_LIB)
	@$(MAKE) $(LIBGR_LIB)

libclean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(LIBGR_DIR) clean

libfclean:
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(LIBGR_DIR) fclean

libre: libfclean lib

libnorm:
	@$(MAKE) -C $(LIBFT_DIR) norm
	@$(MAKE) -C $(LIBGR_DIR) norm

.PHONY: all clean libclean fclean libfclean re libre norm libnorm

-include $(OBJECTS:.o=.d)

# -- DISPLAY --

LEN_NAME =	`printf "%s" $(NAME) |wc -c`
DELTA =		$$(echo "$$(tput cols)-51-$(LEN_NAME)"|bc)
NB =		$(words $(FILES))
INDEX=		0

ERASELN =	\033[K
CNO =		\033[38;5;%dm

YELLOW =	\e[31;33m
YELLOW_B =	\e[31;33;1m
GREEN =		\e[32m
GREEN_B =	\e[32;1m
RED =		\e[31m
RED_B =		\e[31;1m
WHITE =		\e[37m
WHITE_B =	\e[37;1m
EOC =		\e[0m
