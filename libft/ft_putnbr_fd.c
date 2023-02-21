/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwpark <kwpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 21:45:15 by kwpark            #+#    #+#             */
/*   Updated: 2022/03/23 08:20:18 by kwpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	char	digit;

	if (nb == -2147483648)
		write (fd, "-2147483648", 11);
	else if (nb < 0)
	{
		write (fd, "-", 1);
		ft_putnbr_fd(nb * -1, fd);
	}
	else if (nb >= 10)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	else
	{
		digit = nb + '0';
		write (fd, &digit, 1);
	}
}
