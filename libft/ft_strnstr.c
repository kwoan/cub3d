/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwpark <kwpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:30:56 by kwpark            #+#    #+#             */
/*   Updated: 2022/03/14 21:26:43 by kwpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_find(const char *str, const char *find, size_t i, size_t n)
{
	while (*str && *find && (*str == *find) && i < n)
	{
		str++;
		find++;
		i++;
	}
	return (*find == '\0');
}

char	*ft_strnstr(const char *str, const char *find, size_t n)
{
	size_t	i;

	i = 0;
	if (*find == '\0')
		return ((char *)str);
	while (str[i] && i < n)
	{
		if (str[i] == *find)
			if (is_find(str + i, find, i, n))
				return ((char *)(str + i));
		i++;
	}
	return (NULL);
}
