/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhenriqu <hhenriqu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:25:36 by hhenriqu          #+#    #+#             */
/*   Updated: 2023/03/13 20:06:42 by hhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}	t_dlist;

typedef struct s_flags
{
	int	f_minus;
	int	f_zero;
	int	p_dot;
	int	f_hash;
	int	f_space;
	int	f_plus;
	int	f_width;
}	t_flags;

void	ft_bzero(void *s, size_t n);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);
int		ft_isspace(int c);

void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

char	*ft_strjoin2(char const *s1, char const *s2, int free_s1, int free_s2);

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);

int		ft_toupper(int c);
int		ft_tolower(int c);

void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);

int		ft_atoi(const char *str);
long	int	ft_atol(const char *str);

int		ft_printf(const char *str, ...);
int		ft_resolve_chr(char c, t_flags flags);
int		ft_resolve_str(char *str, t_flags flags);
int		ft_resolve_dec(int n, t_flags flags);
int		ft_resolve_hex(unsigned long long n, int is_upper, t_flags flags);
int		ft_resolve_ptr(unsigned long long ptr, t_flags flags);
int		ft_resolve_uns(unsigned int n, t_flags flags);
int		ft_put_space(int spaces, int str_len);
int		ft_num_len(unsigned int n, int base);
int		ft_num_len_int(int n);
void	ft_putnbr_hex(unsigned long long n, int is_upper, int n_zeros);
void	ft_putuns_zero(unsigned int n, int n_zeros);
void	ft_putnbr_zero(int n, int n_zeros, int len);
void	ft_handle_zero_dot(unsigned int n, int *num_len, t_flags *flags);
char	*ft_flg_get(t_flags *flags, char *src);
t_flags	ft_flg_init(void);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

int		ft_dlstsize(t_dlist *lst);
t_dlist	*ft_dlstnew(void *content);
t_dlist	*ft_dlstlast(t_dlist *lst);
t_dlist	*ft_dlstfirst(t_dlist *lst);
t_dlist	*ft_dlstmap(t_dlist *lst, void *(*f)(void *), void (*del)(void *));
void	ft_dlstadd_front(t_dlist **lst, t_dlist *new);
void	ft_dlstadd_back(t_dlist **lst, t_dlist *new);
void	ft_dlstdelone(t_dlist *lst, void (*del)(void*));
void	ft_dlstclear(t_dlist **lst, void (*del)(void*));
void	ft_dlstiter(t_dlist *lst, void (*f)(void *));

#endif