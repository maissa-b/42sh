/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:15:23 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/03 21:15:23 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*ref;
	t_list	*tmp1;
	t_list	*tmp2;

	if (!lst || !f)
		return (NULL);
	if (!(ref = ft_lstnew(lst->content, lst->content_size)))
		return (NULL);
	ref = (*f)(ref);
	tmp1 = ref;
	lst = lst->next;
	while (lst)
	{
		if (!(tmp2 = ft_lstnew(lst->content, lst->content_size)))
			return (NULL);
		tmp2 = (*f)(tmp2);
		tmp1->next = tmp2;
		tmp1 = tmp1->next;
		lst = lst->next;
	}
	return (ref);
}
