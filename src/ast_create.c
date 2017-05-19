/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:18 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/08 23:30:49 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

#define LENLIB  11

t_tree			*init_node(void)
{
	t_tree	*node;

	if (!(node = ft_memalloc(sizeof(t_tree))))
		return (NULL);
	ft_memset(node, 0, sizeof(node));
	return (node);
}

static t_lib	g_lib_op[LENLIB] =
{
	{.toke = DOT, .priority = 11},
	{.toke = OR, .priority = 10},
	{.toke = AND, .priority = 10},
	{.toke = PIPE, .priority = 8},
	{.toke = SL_DIR, .priority = 7},
	{.toke = SR_DIR, .priority = 7},
	{.toke = DL_DIR, .priority = 7},
	{.toke = DR_DIR, .priority = 7},
	{.toke = LR_DIR, .priority = 7},
	{.toke = DIR_L_AMP, .priority = 7},
	{.toke = DIR_R_AMP, .priority = 7},
};

t_tree			*add_tree(t_token *lst)
{
	t_tree *node;

	node = ft_memalloc(sizeof(t_tree));
	node->token_or = lst;
	node->cmd = NULL;
	node->father = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

static t_lib	*check_lib(t_token *node)
{
	int i;

	i = 0;
	while (i < LENLIB)
	{
		if (node->type == g_lib_op[i].toke)
			return (&g_lib_op[i]);
		++i;
	}
	return (NULL);
}

/*
** compare les operateur par rappot à la g_lib_op
*/

int				compare_token_op(t_token *node_lst, t_token *tmp)
{
	t_lib	*lib_lst;
	t_lib	*lib_tmp;

	lib_lst = NULL;
	lib_lst = check_lib(node_lst);
	lib_tmp = NULL;
	lib_tmp = check_lib(tmp);
	if (!lib_lst && lib_tmp)
		return (1);
	else if (lib_lst && lib_tmp)
	{
		if (lib_lst->priority == lib_tmp->priority && lib_lst->priority > 10)
			return (0);
		if (lib_lst->priority <= lib_tmp->priority)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

/*
**    regle pour parser la liste et inserer les token au bon endroit
*/

int				priority(t_token *node_lst, t_token *tmp)
{
	if (!node_lst && tmp->select == 0)
		return (1);
	else if (compare_token_op(node_lst, tmp))
		return (1);
	else if (!node_lst && tmp->type == CMD)
		return (1);
	return (0);
}
