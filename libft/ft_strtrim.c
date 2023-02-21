/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwpark <kwpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:36:47 by kwpark            #+#    #+#             */
/*   Updated: 2022/03/23 06:49:12 by kwpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*res;

	if (!s1)
		return (0);
	start = 0;
	if (!ft_strlen(s1))
		end = ft_strlen(s1);
	else
		end = ft_strlen(s1) - 1;
	while (s1[start] && (ft_strchr(set, s1[start]) != NULL))
		start++;
	while (s1[end] && (ft_strchr(set, s1[end]) != NULL) && (end > start))
		end--;
	res = ft_substr(s1, start, end - start + 1);
	return (res);
}
