/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwpark <kwpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:21:12 by kwpark            #+#    #+#             */
/*   Updated: 2022/03/17 21:17:39 by kwpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	int_len(int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*res;
	size_t		i;
	long long	tmp;

	res = malloc(sizeof(char) * (int_len(n) + 1));
	if (!res)
		return (0);
	i = int_len(n);
	tmp = n;
	if (tmp < 0)
	{
		tmp *= -1;
		res[0] = '-';
	}
	res[i] = 0;
	if (!tmp)
		res[--i] = '0';
	while (tmp)
	{
		res[--i] = tmp % 10 + '0';
		tmp /= 10;
	}
	return (res);
}
