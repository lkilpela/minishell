# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/12 14:15:32 by aklein            #+#    #+#              #
#    Updated: 2024/06/10 02:54:00 by aklein           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
# COMPILATION
################################################################################
CC				=	cc
CC_STRICT		=	-Wall -Wextra -Werror
DB_FLAGS		=	-g #-fsanitize=leak
HEADERS			=	-I $(LIBFT_INCLUDES) -I $(INCLUDES) \
					-I/opt/homebrew/opt/readline/include \
					-I ~/.brew/Cellar/readline/8.2.10/include
CC_FULL			=	$(CC) $(CC_STRICT) $(DB_FLAGS) $(HEADERS)

################################################################################
# LIBFT
################################################################################
LIBFT			=	./libft/libft.a
LIBFT_DIR		=	./libft
LIBFT_INCLUDES	=	./libft/include

################################################################################
# READLINE
################################################################################
READLINE		=	-L/opt/homebrew/opt/readline/lib \
					-L ~/.brew/Cellar/readline/8.2.10/lib \
					-lreadline

################################################################################
# MANDATORY
################################################################################
NAME			=	minishell
INCLUDES		=	./include
M_HEADERS		=	$(INCLUDES)/minishell.h \
					$(INCLUDES)/structs.h \
					$(INCLUDES)/errors.h
OBJ_DIR			=	./obj
OBJECTS			=	$(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))
SRC_DIR			=	./src
SRCS			=	minishell.c \
					init.c \
					tokenization.c \
					token_list.c \
					token_utils.c \
					token_utils1.c \
					token_utils2.c \
					var_expander.c \
					var_handler.c \
					var_list.c \
					var_list_utils.c \
					var_misc.c \
					merge_sort_vars.c \
					list_to_list.c \
					parsing.c \
					parser_utils.c \
					simple_cmd.c \
					redirection.c \
					heredoc.c \
					builtins.c \
					built_pwd.c \
					built_echo.c \
					built_cd.c \
					built_env.c \
					built_export.c \
					built_unset.c \
					built_exit.c \
					path.c \
					exec.c \
					child.c \
					validate.c \
					signals.c \
					errors.c \
					print_err.c \
					ms_exit.c \
					lalloc.c \
					safe_alloc1.c \
					safe_alloc2.c \
					print_and_free.c \

################################################################################
# RULES
################################################################################

#this means that every time its looking for a match for %.c
#													in there
#											$(OBJ_DIR)/%.o: %.c $(M_HEADERS)
#
#it will look throuhg all these directories to find the file
#this way we dont have to specify folders in front of each file
#just have to make sure each file in the $(SRCS) is a unique name
vpath %.c $(SRC_DIR) $(SRC_DIR)/tokenizer \ $(SRC_DIR)/execution\
			$(SRC_DIR)/env_var $(SRC_DIR)/parser $(SRC_DIR)/builtins \
			$(SRC_DIR)/error $(SRC_DIR)/signals

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@echo "--------------------------------------------"
	@$(CC_FULL) $(OBJECTS) $(LIBFT) $(READLINE) -o $(NAME)
	@echo "[$(NAME)] $(BLUE)Built target $(NAME)$(RESET)"
	@echo "--------------------------------------------"

$(OBJ_DIR)/%.o: %.c $(M_HEADERS)
	@mkdir -p $(@D)
	@$(CC_FULL) -c $< -o $@
	@echo "$(GREEN)Compiled: $< $(RESET)"

$(LIBFT): libft_force
	@make -C $(LIBFT_DIR)

libft_force:
	@true

clean:
	@rm -rf $(NAME).dSYM/ obj/
	@make clean -C $(LIBFT_DIR)
	@echo "[$(NAME)] Object files cleaned."

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@echo "[$(NAME)] Everything deleted."

re: fclean all
	@echo "[$(NAME)] Everything rebuilt."

################################################################################
# NORM
################################################################################
norm:
	norminette . $(LIBFT_DIR) | grep -v "OK!" || true

norm2:
	norminette . $(LIBFT_DIR)

################################################################################
# PHONY
################################################################################
.PHONY: all bonus re clean fclean libft_force db

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
BLUE = \033[34m

################################################################################
# VALGRIND
################################################################################

CC_VG = $(CC) $(CC_STRICT) $(HEADERS)

VG = valgrind

VG_FLAGS = --leak-check=full \
	--show-leak-kinds=all \
	--trace-children=yes \
	--suppressions=readline.supp

VG_LOG_FLAGS = $(VG_FLAGS) \
	--log-file=$(VG_LOG) \
	--track-origins=yes \
	--verbose \
	--gen-suppressions=all

VG_LOG = valgrind_leaks.log

vg: vg_build
	$(VG) $(VG_FLAGS) ./$(NAME) $(VG_ARGS)

vglog: vg_build
	$(VG) $(VG_LOG_FLAGS) ./$(NAME) $(VG_ARGS)

vg_build: $(OBJECTS)
	$(CC_FULL) $(OBJECTS) $(READLINE) $(LIBFT) -o $(NAME)

vglog_clean: fclean
	rm -f $(VG_LOG)