# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/12 14:15:32 by aklein            #+#    #+#              #
#    Updated: 2024/05/20 14:41:05 by lkilpela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
# COMPILATION
################################################################################
CC				=	cc
CC_STRICT		=	-Wall -Wextra -Werror
DB_FLAGS		=	-g #-fsanitize=leak
HEADERS			=	-I $(LIBFT_INCLUDES) -I $(INCLUDES)
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
READLINE		=	-lreadline

################################################################################
# MANDATORY
################################################################################
NAME			=	minishell
INCLUDES		=	./include
M_HEADERS		=	$(INCLUDES)/minishell.h \
					$(INCLUDES)/structs.h
OBJ_DIR			=	./obj
OBJECTS			=	$(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))
SRC_DIR			=	./src
SRCS			=	minishell.c \
					token_utils.c \
					token_utils2.c \
					token_utils3.c \
					var.c \
					init.c \
					tokenizer.c \
					quote_handler.c \
					print_and_free.c \
					expander.c \
					parsing.c \
					built_pwd.c \
					built_echo.c \
					built_cd.c
					
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
vpath %.c $(SRC_DIR) $(SRC_DIR)/tokenizer $(SRC_DIR)/parser $(SRC_DIR)/builtins

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@echo "--------------------------------------------"
	@$(CC_FULL) $(OBJECTS) $(READLINE) $(LIBFT) -o $(NAME)
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