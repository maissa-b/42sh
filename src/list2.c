/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:34 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/03 21:13:34 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	insert_link_top(t_list **ref_head_top, t_list *sub_link_chain)
{
	t_list	*link;

	link = sub_link_chain;
	while (link->next)
		link = link->next;
	link->next = *ref_head_top;
	*ref_head_top = sub_link_chain;
}

void	insert_link_bottom(t_list **ref_head_top, t_list *sub_link_chain)
{
	while (*ref_head_top)
		ref_head_top = &(*ref_head_top)->next;
	*ref_head_top = sub_link_chain;
}

void	list_iter(t_list *list, void (f)(void *))
{
	while (list)
	{
		f(list->content);
		list = list->next;
	}
}

void	*list_iter_while(t_list *list, void *(f)(void *))
{
	void	*result;

	while (list)
	{
		if ((result = f(list->content)))
			return (result);
		list = list->next;
	}
	return (NULL);
}

void	*list_get_nth(t_list *list, uint32_t nth)
{
	while (list)
	{
		--nth;
		if (!nth)
			return (list->content);
		list = list->next;
	}
	return (NULL);
}
