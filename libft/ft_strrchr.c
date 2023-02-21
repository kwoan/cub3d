/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwpark <kwpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 18:54:35 by kwpark            #+#    #+#             */
/*   Updated: 2022/03/13 22:25:47 by kwpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*tmp;

	tmp = NULL;
	while (*str)
	{
		if (*str == (char)c)
			tmp = (char *)str;
		str++;
	}
	if (*str == (char)c)
		tmp = (char *)str;
	return (tmp);
}
