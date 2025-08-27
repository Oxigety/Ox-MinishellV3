/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babou <babou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 07:40:20 by bchapuis          #+#    #+#             */
/*   Updated: 2024/03/02 13:20:28 by babou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c );
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	*ft_memchr(const void *str, int search, size_t n);
int		ft_memcmp(const void *str1, const void *str2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset( void *p, int v, size_t c);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *str, int search);
char	*ft_strdup(const char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
int		ft_strncmp( const char *first, const char *second, size_t length );
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr( const char *str, int search);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_printf(const char *str, ...);
int		ft_putnbr(int n);
int		ft_puthexanbr(unsigned long n, char *str);
int		ft_putunsignnbr(unsigned int n);
int		ft_putstr(char *str);
int		ft_putchar(char c);
int		ft_ptr(unsigned long n, char *hex);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr( const char *s, int search);

char	*ft_get_line(char *stock, char *buff, int nbr);
char	*read_line(int fd, char *stock, char *buff, int *nbr);
char	*get_next_line(int fd);
int		find_newline(char *stock);

char	*ft_grab_line(char *s, size_t n);
size_t	get_bn(char *buf);
size_t	ft_strlen2(const char *s, size_t n);
char	*ft_strjoin2(char const *s1, char const *s2);
void	*ft_memmove2(void *dest, const void *src, size_t n);
void	ft_bzero2(void *s, size_t n);
void	ft_clean_buffer(char *buf);
char	*ft_strdup2(const char *s);
char	*read_rest(int fd, char buffer[BUFFER_SIZE + 1], char *ret, int *end);

#endif
