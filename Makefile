CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBREADLINEFLAGS = -lreadline
NAME = minishell
NAME_H = minishell.h
LIBFT = libft.a
LIBFT_DIR = libft
LIBFT_H = libft.h
SRC = \
create_env_list.c \
create_proc_list.c \
expand_string.c expand_token_list.c \
main.c \
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
