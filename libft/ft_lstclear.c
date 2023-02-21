/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwpark <kwpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 02:24:19 by kwpark            #+#    #+#             */
/*   Updated: 2022/03/24 21:50:12 by kwpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*remove;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst)
	{
		remove = *lst;
		*lst = (*lst)->next;
		del(remove->content);
		free(remove);
	}
}
