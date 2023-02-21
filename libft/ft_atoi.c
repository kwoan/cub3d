/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwpark <kwpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 17:35:54 by kwpark            #+#    #+#             */
/*   Updated: 2022/03/24 00:40:38 by kwpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(const char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	ft_get_sign(const char **str)
{
	if (**str == '-')
	{
		(*str)++;
		return (-1);
	}
	else if (**str == '+')
	{
		(*str)++;
		return (1);
	}
	else
		return (1);
}

unsigned long long	ft_max_val(int sign)
{
	unsigned long long	res;

	res = (unsigned long long)1 << 63;
	if (sign > 0)
		res--;
	return (res);
}

int	ft_atoi(const char *str)
{
	unsigned long long	tmp;
	unsigned long long	max_val;
	int					sign;

	tmp = 0;
	while (ft_isspace(*str))
		str++;
	sign = ft_get_sign(&str);
	max_val = ft_max_val(sign);
	while (*str >= '0' && *str <= '9')
	{
		tmp = tmp * 10 + *str - '0';
		if (tmp > max_val)
		{
			tmp = max_val;
			break ;
		}
		str++;
	}
	return (tmp * sign);
}
