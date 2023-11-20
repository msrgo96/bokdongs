NAME = libft.a
CFLAGS = -Wall -Wextra -Werror
INC = ../
SRCS_DIR = sources
OBJS_DIR = obj

SRCS_FILE = ft_isalpha.c ft_isdigit.c ft_isinteger.c ft_isalnum.c ft_isascii.c ft_isprint.c \
ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_calloc.c ft_strlcpy.c \
ft_striteri.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_memmove.c ft_strdup.c \
ft_strlcat.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
ft_substr.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
ft_new_str.c ft_str_append.c \
\
ft_memchr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_isspace.c ft_intlen.c ft_strtol.c ft_str_find_chr.c \
ft_puthex_fd.c ft_putptr_fd.c ft_ullen.c ft_putunbr_fd.c \
\
ft_new_node.c ft_list_append.c ft_listsize.c ft_listlast.c \
ft_list_iter.c ft_list_clear.c\
ft_listget.c ft_free_list.c ft_new_list.c\
ft_list_is_empty.c ft_list_pop.c \
ft_del_node.c ft_del_node_and_link.c \
ft_get_node_idx.c ft_insert_list_at.c \
ft_replace_node_with_list.c \
\
ft_printf.c ft_strcmp.c ft_isnum.c ft_math.c \
get_next_line.c get_next_line_utils.c \
ft_free.c
OBJS_FILE = $(SRCS_FILE:.c=.o)

SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILE))
OBJS = $(addprefix $(OBJS_DIR)/, $(OBJS_FILE))

.PHONY = all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $@ $^

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	cc $(CFLAGS) -I$(INC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:
	make fclean
	make all
