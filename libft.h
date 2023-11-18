/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:59:31 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/18 00:19:14 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# if defined __x86_64__ && !defined __ILP32__

#  define FT_LONG_MAX 9223372036854775807L

# else

#  define FT_LONG_MAX 2147483647L

# endif

# define FT_INT_MAX 2147483647

# define FT_HEX "0123456789abcdef"

typedef struct s_node
{
	void			*content;
	struct s_node	*next;
	struct s_node	*prv;
}	t_node;

typedef struct s_list
{
	t_node	*head;
	t_node	*tail;
}	t_list;

typedef struct s_point
{
	int	i;
	int	j;
}	t_point;

size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
long	ft_strtol(const char *str);
int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isinteger(const char *str);
int		ft_isprint(int c);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(char *s1, char *s2);
int		ft_str_is_same(char *s1, char *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_isspace(int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
int		ft_str_find_chr(char *str, char c);

int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
int		ft_putendl_fd(char *s, int fd);
int		ft_putnbr_fd(int n, int fd);
int		ft_putunbr_fd(unsigned int n, int fd);
int		ft_putptr_fd(void *ptr, int fd);
int		ft_puthex_fd(size_t n, int is_upper, int fd);
char	*ft_tohex(size_t n, int is_upper);
int		ft_intlen(int n);
int		ft_ullen(size_t n, int base);
char	*ft_tohex(size_t n, int is_upper);

t_list	*ft_new_list(void);
t_node	*ft_new_node(void *content);
int		ft_listsize(t_list *list);
t_node	*ft_listlast(t_list *list);
void	ft_list_clear(t_list *list, void (*del)(void *));
void	ft_list_iter(t_list *list, void (*f)(void *));
t_list	*ft_list_iter_reassign(t_list *list, void *(*f)(void *));
t_node	*ft_listget(t_list *list, int i);
t_node	*ft_list_pop(t_list *list);
void	ft_list_append(t_list *list, t_node *new);
void	ft_list_append_front(t_list *list, t_node *new);
int		ft_list_is_empty(t_list *list);
void	ft_del_node(t_node *node, void (*del)(void *));
void	ft_del_node_and_link(t_list *list, t_node *target, void (*del)(void *));
void	ft_free_list(t_list *list);
void	ft_free_list_with_content(t_list *list);
int		ft_get_node_idx(t_list *list, t_node *target);
void	ft_insert_list_at(t_list *base, t_list *insert, int at);
void	ft_replace_node_with_list(t_list *base, t_list *sub, t_node *node);

int		ft_printf(const char *format, ...);
int		ft_isnum(char *input);
void	ft_split_free(char **s);

double	absolute(double x);
double	sqrt(double n);

int		free_and_return(char *data);
char	*get_next_line(int fd);
char	*ft_strcat(char *s, char *buffer, ssize_t size);
ssize_t	ft_strchr_idx(char *s, char c, size_t offset);

void	two_d_free(void **p);

#endif
