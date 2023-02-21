/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwpark <kwpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:29:28 by kwpark            #+#    #+#             */
/*   Updated: 2022/03/24 21:49:05 by kwpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	word_count(char const *src, char c)
{
	int	count;

	count = 0;
	while (*src == c && *src)
		src++;
	while (*src)
	{
		while ((*src != c) && *src)
			src++;
		count++;
		while (*src == c && *src)
			src++;
	}
	return (count);
}

size_t	strlen_del(char const *str, char c)
{
	size_t	len;

	len = 0;
	while (str[len] && (str[len] != c))
		len++;
	return (len);
}

int	free_all(char **res, size_t i)
{
	if (!res[i])
	{
		while (--i >= 0)
			free(res[i]);
		free(res);
		return (1);
	}
	else
		return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	i;

	if (!s)
		return (0);
	res = malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!res)
		return (0);
	i = 0;
	while (*s)
	{
		if (strlen_del(s, c) > 0)
		{
			res[i] = ft_substr(s, 0, strlen_del(s, c));
			if (free_all(res, i))
				return (0);
			i++;
		}
		s += strlen_del(s, c);
		if (*s != 0)
			s++;
	}
	res[i] = 0;
	return (res);
}
