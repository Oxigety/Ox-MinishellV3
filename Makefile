# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bchapuis <bchapuis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/30 22:25:01 by bchapuis          #+#    #+#              #
#    Updated: 2024/01/30 22:25:01 by bchapuis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Wextra -Werror -g3
INC = -Iincludes/ -I$(LIB_DIR)/includes 
LIB_DIR = libft/
SRC_DIR = source/
OBJ_DIR = objs/
HEADERS = includes/minishell.h
LIB = $(LIB_DIR)libft.a

SRC_NAME =	main.c\
			signals.c\
			prompt.c\
			ft_printf_err_utils.c\
			ft_printf_err.c\
			builtins/exit.c\
			builtins/cd.c\
			builtins/cd_utils.c\
			builtins/echo.c\
			builtins/env.c\
			builtins/env_utils.c\
			builtins/pwd.c\
			builtins/unset.c\
			builtins/export.c\
			builtins/export_utils.c\
			heredoc/heredoc.c\
			heredoc/handle_heredoc.c\
			heredoc/handle_heredoc2.c\
			heredoc/heredoc_utils.c\
			heredoc/heredoc_utils2.c\
			heredoc/heredoc_utils3.c\
			heredoc/heredoc_utils4.c\
			exec/cmd_utils.c\
			exec/build_exec.c\
			exec/build_cmd_utils.c\
			exec/execute_cmd_list.c\
			exec/manage_redir.c\
			exec/redir_types.c\
			exec/exec_cmd.c\
			exec/exec_no_path.c\
			exec/find_exec.c\
			utils/expand_utils.c\
			utils/expand_utils2.c\
			utils/quotes.c\
			utils/str_utils.c\
			utils/util.c\
			utils/utils2.c\
			utils/utils3.c\
			utils/getters.c\
			utils/free_utils.c\
			utils/free_utils2.c\
			utils/error.c\
			utils/char_utils.c\
			utils/split_args.c\
			utils/is_valid.c\
			utils/is_valid2.c\
			utils/is_r_valid.c

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_DIR),$(OBJ_NAME))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS) Makefile
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/builtins
	@mkdir -p $(OBJ_DIR)/exec
	@mkdir -p $(OBJ_DIR)/heredoc
	@mkdir -p $(OBJ_DIR)/utils
	@echo "##### Creating" [ $@ ] " #####"
	@cc $(FLAGS) -o $@ -c $< $(INC)

$(NAME): $(OBJ) $(LIB)
	@cc -o $(NAME) $(OBJ) -L $(LIB_DIR) -lft -lreadline
	@echo "\033[0;32m##### minishell created #####\033[0m"

all: $(NAME)

$(LIB) : FORCE
	@make -C $(LIB_DIR) --silent

clean:
	@make -C $(LIB_DIR) clean  --silent
	@rm -f $(CHECK_OBJ) $(OBJ)
	@rm -r $(OBJ_DIR)
	@echo "\033[0;33m##### Removed object files #####\033[0m"

fclean: clean
	@make -C $(LIB_DIR) fclean  --silent
	@rm -f $(NAME)
	@echo "\033[0;33m##### Removed binary files #####\033[0m"

re: fclean all

FORCE :

.PHONY: all clean fclean re FORCE
