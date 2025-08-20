# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 18:51:17 by yelu              #+#    #+#              #
#    Updated: 2025/04/28 18:51:17 by yelu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# clang main.c -lpthread <-- must use this flag when compiling to use POSIX thread library

# Colors
RED		=	\033[1;31m
GREEN	=	\033[1;32m
YELLOW	=	\033[1;33m
BLUE	=	\033[1;34m
PINK 	=	\033[35m
RESET	=	\033[0m

# Program name
NAME = philo

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
INC = -I$(INC_DIR)

# Compiler & flags
CC = clang
CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address
RM = rm -rf

# Source files
SRC = $(addprefix $(SRC_DIR)/, \
		main.c \
		utils.c \
		death.c \
		init.c \
		parsing.c \
		routine.c \
		time.c)

# Object files
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Build rules
all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "$(YELLOW)Compiled ✅ $(GREEN) $(BOLD) $< $(RESET)"

$(NAME): $(OBJ) 
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)  -lpthread
	@echo "$(GREEN)$(BOLD)✅ Build Successful: $(NAME)$(RESET)"

# Build library folder
$(OBJ_DIR): FORCE
	@mkdir -p $(OBJ_DIR)

# Clean object files and executable
clean:
	@echo "$(RED)❌ Deleting\t$(RESET)$(WHITE)Objects$(RESET)\t$(OBJ_DIR)";
	@$(RM) $(OBJ_DIR)
	@echo "$(GREEN)✅ Removed\t$(RESET)$(WHITE)Objects$(RESET)"

fclean: clean
	@echo "$(RED)❌ Deleting libraries$(RESET)"
	@echo "$(RED)❌ Deleting$(RESET)\t$(NAME)"
	@$(RM) $(NAME)
	@echo "$(GREEN)✅ Removed\t$(RESET)$(WHITE)$(NAME)$(RESET)"

re: fclean all

# # debug:
#@echo "SRC: $(SRC)"
#@echo "OBJ: $(OBJ)"
#@echo "OBJ_DIR: $(OBJ_DIR)"

FORCE:

.PHONY: bonus all clean fclean re

# -I(include directory) - Tells the compiler to look for header files 
# -L(directory) - Tells the compiler to look for .a library path in this folder
# -l(%.a) - Tells the compiler to look for that specified .a file
