/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:15:23 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/03 21:15:23 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpush(t_list **begin, void const *s, size_t s_size)
{
	t_list	*elem;

	elem = *begin;
	if (elem == NULL)
		return ;
	while (elem->next)
		elem = elem->next;
	if (!elem->next)
	{
		elem->next = ft_lstnew(s, s_size);
		return ;
	}
	else
		elem->next = ft_lstnew(s, s_size);
	return ;
}
