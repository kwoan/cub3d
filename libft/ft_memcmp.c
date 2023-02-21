/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwpark <kwpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 20:10:21 by kwpark            #+#    #+#             */
/*   Updated: 2022/03/14 11:43:13 by kwpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*tmp1;
	const unsigned char	*tmp2;
	size_t				i;

	tmp1 = s1;
	tmp2 = s2;
	i = 0;
	if (!n)
		return (0);
	while ((tmp1[i] == tmp2[i]) && (i + 1 < n))
		i++;
	return (tmp1[i] - tmp2[i]);
}
