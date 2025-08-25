# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 21:26:43 by jose-jim          #+#    #+#              #
#    Updated: 2025/08/25 15:50:31 by jescuder         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

# The name of the executable
NAME = minishell

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Command to remove files/directories
REMOVE = rm -rf
# Command to create directories
MKDIR = mkdir -p

# Paths
SRCS_PATH = src/
OBJS_PATH = objs/
INC_PATH = inc/
LIBFT_PATH = $(INC_PATH)libft/

# Source files
SRC = $(wildcard $(SRCS_PATH)*.c)

# Object files
OBJS = $(patsubst $(SRCS_PATH)%.c, $(OBJS_PATH)%.o, $(SRC))

# Compiler flags to link libraries
LFLAGS = -L$(LIBFT_PATH) -lft -lreadline

# Prevents all commands from showing in the shell.
.SILENT:

.PHONY: all libft clean fclean re norm

all: libft $(NAME)

# Runs the libft Makefile, which will compile libft.a if its dependencies have changed.
libft:
	$(MAKE) -C $(LIBFT_PATH) --no-print-directory

# Compiles the mandatory part.
$(NAME): $(LIBFT_PATH)libft.a $(OBJS_PATH) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)
	echo "$(GREEN)[$(NAME)] executable compiled.$(DEF_COLOR)"

# Compiles libft.a if it's missing.
$(LIBFT_PATH)libft.a:
	$(MAKE) -C $(LIBFT_PATH) --no-print-directory

# Creates the objects directory if it doesn't exist.
$(OBJS_PATH):
	$(MKDIR) $(OBJS_PATH)
	echo "$(YELLOW)[$(OBJS_PATH)] directory created.$(DEF_COLOR)"

# Compiles C source files into object files.
$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(INC_PATH)$(NAME).h
	$(CC) $(CFLAGS) -I $(INC_PATH) -I $(LIBFT_PATH) -c $< -o $@
	echo "$(CYAN)[$@] object compiled.$(DEF_COLOR)"

clean:
	$(REMOVE) $(OBJS_PATH)
	echo "$(MAGENTA)[$(NAME)] objects directory and files cleaned.$(DEF_COLOR)"
	$(MAKE) clean -C $(LIBFT_PATH) --no-print-directory

fclean:
	$(REMOVE) $(OBJS_PATH)
	echo "$(MAGENTA)[$(NAME)] objects directory and files cleaned.$(DEF_COLOR)"
	$(REMOVE) $(NAME)
	echo "$(BLUE)[$(NAME)] executable cleaned.$(DEF_COLOR)"
	$(MAKE) fclean -C $(LIBFT_PATH) --no-print-directory

re: fclean all

norm:
	norminette $(SRCS_PATH) $(INC_PATH)
