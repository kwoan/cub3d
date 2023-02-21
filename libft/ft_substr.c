/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwpark <kwpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:58:51 by kwpark            #+#    #+#             */
/*   Updated: 2022/03/22 17:09:06 by kwpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	alloc_size;

	if (!s)
		return (0);
	if (start > (unsigned int)ft_strlen(s))
		alloc_size = 0;
	else if (ft_strlen(s) - start > len)
		alloc_size = len;
	else
		alloc_size = ft_strlen(s) - start;
	res = (char *)malloc(sizeof(char) * (alloc_size + 1));
	if (!res)
		return (0);
	i = 0;
	while (i < alloc_size)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
