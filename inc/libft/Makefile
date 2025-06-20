# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/26 12:12:48 by jose-jim          #+#    #+#              #
#    Updated: 2025/04/22 21:38:28 by jose-jim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar -rcs

SRC = chars/ft_putchar.c \
		chars/ft_putstr.c \
		chars/ft_putptr.c \
		chars/ft_isalnum.c \
		chars/ft_isalpha.c \
		chars/ft_isascii.c \
		chars/ft_isdigit.c \
		chars/ft_isnum.c \
		chars/ft_isprint.c \
		chars/ft_putnbr.c \
		chars/ft_puthex.c \
		chars/ft_tolower.c \
		chars/ft_toupper.c \
		conversions/ft_atoi.c \
		conversions/ft_atol.c \
		conversions/ft_itoa.c \
		file_desc/ft_putchar_fd.c \
		file_desc/ft_putstr_fd.c \
		file_desc/ft_putendl_fd.c \
		file_desc/ft_putnbr_fd.c \
		file_desc/ft_countlines_fd.c \
		memory/ft_bzero.c \
		memory/ft_calloc.c \
		memory/ft_memcpy.c \
		memory/ft_memmove.c \
		memory/ft_memchr.c \
		memory/ft_memcmp.c \
		memory/ft_memset.c \
		memory/ft_strdup.c \
		strings/ft_strlen.c \
		strings/ft_strlcpy.c \
		strings/ft_strlcat.c \
		strings/ft_strchr.c \
		strings/ft_strrchr.c \
		strings/ft_strncmp.c \
		strings/ft_strnstr.c \
		strings/ft_substr.c \
		strings/ft_strjoin.c \
		strings/ft_strtrim.c \
		strings/ft_split.c \
		strings/ft_strmapi.c \
		strings/ft_striteri.c \
		math/ft_mean.c \
		math/ft_abs.c \
		math/ft_max.c \
		math/ft_min.c \
		ft_printf/ft_printf.c \
		get_next_line/get_next_line.c \


# .c files = .o files
OBJ = $(SRC:.c=.o)

# Colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

# compilation and linking
all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo "$(GREEN) [LIBFT] Library compiled $(DEF_COLOR)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)
	@echo "$(BLUE) [LIBFT] Object files cleaned!$(DEF_COLOR)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(BLUE) [LIBFT] Executable files cleaned!$(DEF_COLOR)"

re: fclean all
	@echo "$(BLUE) [LIBFT] Cleaned and rebuilt everything!$(DEF_COLOR)"

.PHONY: all clean fclean re
