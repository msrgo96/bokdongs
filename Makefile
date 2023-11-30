CC = cc
CFLAGS = -Wall -Wextra -Werror -Wno-unknown-pragmas
LIBREADLINEFLAGS = -lreadline
NAME = minishell
NAME_H = minishell.h builtins/builtins.h
LIBFT = libft.a
LIBFT_DIR = libft
LIBFT_H = libft.h
BUILTINS_SRC = builtins/builtins.c builtins/builtins_util.c \
builtins/echo_builtin.c builtins/cd_builtin.c builtins/pwd_builtin.c \
builtins/env_builtin.c builtins/exit_builtin.c builtins/export_builtin.c builtins/unset_builtin.c
EXEC_SRC = exec/executor.c exec/sh_data.c
SRC = main.c $(BUILTINS_SRC) $(EXEC_SRC) \
convert_envp_to_env_list.c \
generate_proc_list.c \
expand_string.c \
parser.c \
split_str_to_list_util.c split_str_to_list.c \
syntax_checker.c \
t_env.c t_proc.c t_redir.c t_token.c \
tokenizer.c
OBJ = $(SRC:%.c=%.o)

all : $(NAME)

# Everytime MUST have to make all LIB_SUBDIR
$(NAME) :
	make -C $(LIBFT_DIR)
ifneq ($(shell find . -name $(NAME) | wc -l | tr -d ' '), 0)
	mv $(NAME) $(NAME).tmp
endif
	make $(NAME).tmp
	mv $(NAME).tmp $(NAME)

# Includes LIB_SUBDIR.TARGET makes LIB_SUBDIR-update
$(NAME).tmp : $(NAME_H) $(OBJ) $(LIBFT_DIR)/$(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_DIR)/$(LIBFT) $(LIBREADLINEFLAGS) -o $(NAME).tmp

clean :
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean : clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re :
	make fclean
	make all

.PHONY : all clean fclean re $(NAME)
