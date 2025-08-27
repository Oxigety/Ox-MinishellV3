# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/14 07:38:03 by bchapuis          #+#    #+#              #
#    Updated: 2024/03/20 09:19:28 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Wextra -Werror -I./includes

SRCS = ft_memset.c\
		ft_memcpy.c\
		ft_isalpha.c\
		ft_isdigit.c\
		ft_putendl_fd.c\
		ft_putstr_fd.c\
		ft_putnbr_fd.c\
		ft_memcpy.c\
		ft_memcmp.c\
		ft_putchar_fd.c\
		ft_atoi.c\
		ft_memchr.c\
		ft_memmove.c\
		ft_strnstr.c\
		ft_itoa.c\
		ft_split.c\
		ft_substr.c\
		ft_isascii.c\
		ft_isprint.c\
		ft_isalnum.c\
		ft_strlen.c\
		ft_bzero.c\
		ft_strdup.c\
		ft_striteri.c \
		ft_strtrim.c\
		ft_tolower.c\
		ft_toupper.c\
		ft_strlcpy.c\
		ft_strjoin.c\
		ft_strlcat.c\
		ft_strmapi.c\
		ft_memcpy.c\
		ft_strncmp.c\
		ft_strrchr.c\
		ft_calloc.c\
		ft_strchr.c\
		ft_printf.c\
		ft_print_nb.c\
		ft_print_str.c\
		get_next_line.c\
		get_next_line_utils.c\

OBJ_NAME = $(SRCS:.c=.o)

OBJ = $(addprefix $(OBJ_DIR),$(OBJ_NAME))
SRC_DIR = srcs/
OBJ_DIR = objs/

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[0;32m##### libft created #####\033[0m"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c includes/libft.h Makefile
	@mkdir -p $(OBJ_DIR)
	@echo "##### Creating libft" [ $@ ] " #####"
	@cc $(FLAGS) -o $@ -c $< $(INC)

clean:
	@rm -f $(OBJ)
	@echo "\033[0;33m##### Removed libft object files #####\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;33m##### Removed libft.a #####\033[0m"

re: fclean all

.PHONY: all clean fclean re
