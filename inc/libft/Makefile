# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/26 12:12:48 by jose-jim          #+#    #+#              #
#    Updated: 2025/06/24 16:22:46 by jescuder         ###   ########.fr        #
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

# The name of the library
NAME = libft.a

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Archiver and flags
AR = ar -rcs

# Command to remove files/directories
REMOVE = rm -rf

# Source files
SRC = $(shell find -name '*.c')

# Object files
OBJS = $(SRC:.c=.o)

# Prevents all commands from showing in the shell.
.SILENT:

.PHONY: all clean fclean re

all: $(NAME)

# Compiles the libft.a library.
$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)
	echo "$(GREEN)[libft] library compiled.$(DEF_COLOR)"

# Compiles C source files into object files.
%.o: %.c
	$(CC) $(CFLAGS) -I ./ -c $< -o $@
	echo "$(CYAN)[$@] object compiled.$(DEF_COLOR)"

clean:
	$(REMOVE) $(OBJS)
	echo "$(MAGENTA)[libft] object files cleaned.$(DEF_COLOR)"

fclean: clean
	$(REMOVE) $(NAME)
	echo "$(BLUE)[libft] library cleaned.$(DEF_COLOR)"

re: fclean all
