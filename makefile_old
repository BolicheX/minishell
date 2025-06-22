# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 21:26:43 by jose-jim          #+#    #+#              #
#    Updated: 2025/01/21 15:52:15 by jose-jim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# The name of the executable
NAME = minishell

# Compilation flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
# Linker flags : 'libft'
LFLAGS = -lft

# Command to remove files/directories
REMOVE = rm -rf
# Command to create directories
MKDIR = mkdir -p

# Path variables
SRCS_PATH =  ./src/
OBJS_PATH = ./objs/
INC_PATH = ./inc/

# Path to libraries
LIBFT_PATH = $(INC_PATH)libft/

# Source files
SRC = $(wildcard $(SRCS_PATH)*.c)

# Object files
OBJS = $(patsubst $(SRCS_PATH)%.c, $(OBJS_PATH)%.o, $(SRC))

# Compiler flags to link to libraries
LINK_LIBS = -L$(LIBFT_PATH)

# Color codes for terminal output
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

all : $(NAME)

# The target to build the mandatory part
$(NAME) : $(OBJS)
		@make -C $(LIBFT_PATH) --no-print-directory
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LINK_LIBS) $(LFLAGS)
		@echo "$(GREEN) The Makefile of [SO_LONG] has been compiled!$(DEF_COLOR)"

# Compiles C source files into object files
$(OBJS_PATH)%.o : $(SRCS_PATH)%.c
	@$(MKDIR) $(OBJS_PATH)
	@$(CC) $(CFLAGS) -I $(INC_PATH) -c $< -o $@


clean :
	@$(REMOVE) $(OBJS_PATH)
	@make clean -C $(LIBFT_PATH) --no-print-directory
	@echo "$(BLUE)[$(NAME)] Object files cleaned!$(DEF_COLOR)"

fclean : clean
	@$(REMOVE) $(NAME) $(OBJS_PATH)
	@make fclean -C $(LIBFT_PATH) --no-print-directory
	@echo "$(BLUE)[$(NAME)] Executable files and directories cleaned!$(DEF_COLOR)"

re: fclean all

.PHONY: all clean fclean re