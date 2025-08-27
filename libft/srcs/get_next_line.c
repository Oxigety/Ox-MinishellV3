/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Oxigety_ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 09:39:39 by Oxigety_          #+#    #+#             */
/*   Updated: 2023/11/30 17:57:14 by Oxigety_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"

char	*ft_grab_line(char *s, size_t n)
{
	char			*line;
	size_t			i;

	i = 0;
	if (s == NULL || *s == 0)
	{
		free(s);
		return (NULL);
	}
	if (n == 0)
		n = ft_strlen2(s, 0);
	line = (char *)malloc ((sizeof(char) * n) + 1);
	if (line == NULL)
		return (NULL);
	while (i < n && s[i])
	{
		line[i] = s[i];
		i++;
	}
	free(s);
	line[i] = '\0';
	return (line);
}

size_t	get_bn(char *buf)
{
	size_t	i;

	i = 0;
	if (buf == NULL)
		return (0);
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

void	ft_clean_buffer(char *buf)
{
	size_t	lenght;
	size_t	n;

	n = get_bn(buf);
	if (n == 0)
	{
		ft_bzero2(buf, BUFFER_SIZE);
		return ;
	}
	lenght = ft_strlen2(buf, n);
	buf = ft_memmove2(buf, buf + n, lenght);
	buf[lenght] = '\0';
}

char	*read_rest(int fd, char buffer[BUFFER_SIZE + 1], char *ret, int *end)
{
	*end = read(fd, buffer, BUFFER_SIZE);
	buffer[*end] = 0;
	ret = ft_strjoin2(ret, buffer);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = "\0";
	char		*ret;
	size_t		n;
	int			end;

	ret = NULL;
	end = 1;
	if (read(fd, buffer, 0) == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer[0] == '\0')
	{
		end = read(fd, buffer, BUFFER_SIZE);
		buffer[end] = 0;
	}
	ret = ft_strjoin2(ret, buffer);
	if (ret == NULL)
		return (NULL);
	while (get_bn(buffer) == 0 && end && ret != NULL)
		ret = read_rest(fd, buffer, ret, &end);
	n = get_bn(ret);
	ft_clean_buffer(buffer);
	return (ft_grab_line(ret, n));
}
