/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:29 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/08 23:39:18 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**	ft_init_set initialise une nouvelle liste en l'allouant et en mettant tous
**	ses octets a 0, puis retourne la nouvelle liste de type set.
*/

extern t_core	*g_core;

int			ft_init_core(void)
{
	if ((g_core = malloc(sizeof(t_core))) == NULL)
		return (ft_print_error("42sh :", ERR_MALLOC, ERR_EXIT));
	g_core->env = NULL;
	g_core->set = NULL;
	g_core->exp = NULL;
	g_core->hist = NULL;
	return (TRUE);
}

/*
**	ft_init_list initialise une nouvelle liste en l'allouant et en mettant tous
**	ses octets a 0, puis retourne la nouvelle liste de type env.
*/

t_lst		*ft_init_list(void)
{
	t_lst		*lst;

	lst = NULL;
	lst = malloc(sizeof(t_lst));
	if (lst == NULL)
		return (NULL);
	lst->head = NULL;
	lst->tail = NULL;
	lst->size = 0;
	return (lst);
}

/*
**	ft_init_elem initialise un nouvel element en l'allouant et en mettant tous
**	ses octets a 0, puis retourne le nouvel element.
*/

t_elem		*ft_init_elem(void)
{
	t_elem		*elem;

	elem = NULL;
	if ((elem = malloc(sizeof(t_elem))) == NULL)
	{
		return (NULL);
	}
	elem->is_modified = 0;
	elem->is_appended = 0;
	elem->name = NULL;
	elem->value = NULL;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}
