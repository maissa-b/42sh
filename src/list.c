/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:34 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/08 23:47:49 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	*new_link(void *content, size_t content_size)
{
	t_list	*link;

	if ((link = malloc(sizeof(t_list))) == NULL)
		return (NULL);
	ft_bzero(link, sizeof(t_list));
	link->content = content;
	link->content_size = content_size;
	return (link);
}

void	delete_list(t_list **ref_head, void (f)(void *))
{
	void	*ptr;

	while (*ref_head)
	{
		ptr = delete_link(remove_link_top(ref_head));
		if (f && ptr)
			f(ptr);
	}
}

void	*delete_link(t_list *link)
{
	void	*content;

	content = link->content;
	free(link);
	return (content);
}

void	*remove_link_content(t_list **ref_head, void *content)
{
	while (*ref_head)
	{
		if ((*ref_head)->content == content)
			return (remove_link_top(ref_head));
		ref_head = &(*ref_head)->next;
	}
	return (content);
}

void	*remove_link_top(t_list **ref_head_top)
{
	t_list	*link;

	link = *ref_head_top;
	(*ref_head_top) = (*ref_head_top)->next;
	link->next = NULL;
	return (link);
}
