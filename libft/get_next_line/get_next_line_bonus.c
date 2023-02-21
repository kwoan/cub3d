/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwpark <kwpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:02:58 by kwpark            #+#    #+#             */
/*   Updated: 2022/04/07 00:03:59 by kwpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((unsigned char *)s)[i++] = 0;
}

char	*read_file(int fd, char *stored_buf)
{
	char	*tmp;
	char	*buf;
	ssize_t	read_bytes;

	tmp = NULL;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	read_bytes = 1;
	while (!ft_strchr(stored_buf, '\n'))
	{
		ft_bzero(buf, BUFFER_SIZE + 1);
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buf);
			return (NULL);
		}
		else if (read_bytes == 0)
			break ;
		tmp = ft_strjoin(stored_buf, buf);
		free(stored_buf);
		stored_buf = tmp;
	}
	free(buf);
	return (stored_buf);
}

char	*split_line(char *stored_buf)
{
	char	*ret;
	char	*nl_pos;
	size_t	len;

	if (*stored_buf == '\0')
		return (NULL);
	nl_pos = ft_strchr(stored_buf, '\n');
	if (!nl_pos)
		len = ft_strlen(stored_buf);
	else
		len = nl_pos - stored_buf + 1;
	ret = malloc(sizeof(char) * (len + 1));
	ft_strlcpy(ret, stored_buf, len + 1);
	return (ret);
}

char	*split_buf(char *stored_buf)
{
	char	*ret;
	char	*nl_pos;

	ret = NULL;
	nl_pos = ft_strchr(stored_buf, '\n');
	if (nl_pos)
	{
		ret = malloc(sizeof(char) * (ft_strlen(nl_pos + 1) + 1));
		ft_strlcpy(ret, nl_pos + 1, ft_strlen(nl_pos + 1) + 1);
	}
	free(stored_buf);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*stored_buf[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE < 1 || read(fd, NULL, 0) < 0)
		return (NULL);
	if (!stored_buf[fd])
		stored_buf[fd] = ft_strdup("");
	stored_buf[fd] = read_file(fd, stored_buf[fd]);
	if (!stored_buf[fd])
		return (NULL);
	line = split_line(stored_buf[fd]);
	stored_buf[fd] = split_buf(stored_buf[fd]);
	return (line);
}
