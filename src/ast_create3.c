/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:19 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/08 23:30:49 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
** recursive de creation de ast
*/

char			**copy_fd(t_token *tmp)
{
	char	**cmd;

	if (!(cmd = ft_memalloc(sizeof(char *) * 2)))
		return (NULL);
	if (tmp && tmp->word)
	{
		cmd[0] = ft_strdup(tmp->word);
		cmd[1] = NULL;
		return (cmd);
	}
	else
	{
		free(cmd);
		return (NULL);
	}
}

t_tree			*recurs_creat_tree(t_token *lst)
{
	t_token	*tmp;
	t_tree	*node;

	tmp = lst;
	node = NULL;
	node = add_tree(tmp);
	node->token = tmp->type;
	if (tmp->type == CMD)
		node->cmd = concate_cmd(tmp);
	if (is_dir_type(tmp->type))
		node->cmd = copy_fd(tmp);
	if (tmp->type == TARGET)
		node->cmd = copy_fd(tmp);
	node->right = creat_right(tmp);
	if (node->right)
		node->right->father = node;
	node->left = creat_left(tmp);
	if (node->left)
		node->left->father = node;
	return (node);
}

/*
** branche de gauche
*/

t_tree			*creat_left(t_token *lst)
{
	t_token	*tmp;

	tmp = NULL;
	if (!(tmp = search_toke_prev(lst)))
		return (NULL);
	tmp->select = 1;
	return (recurs_creat_tree(tmp));
}

/*
** branche de droite
*/

t_tree			*creat_right(t_token *lst)
{
	t_token	*tmp;

	tmp = NULL;
	if (!(tmp = search_toke(lst)))
		return (NULL);
	tmp->select = 1;
	return (recurs_creat_tree(tmp));
}

/*
** cree la tete de ast
*/

t_tree			*new_tree(t_token *lst)
{
	t_tree	*node;
	t_token	*tmp;

	node = NULL;
	tmp = NULL;
	if (lst)
	{
		tmp = search_toke(lst);
		tmp->select = 1;
		node = add_tree(tmp);
		node->token = tmp->type;
		if (tmp->type == CMD)
			node->cmd = concate_cmd(tmp);
		if (is_dir_type(tmp->type))
			node->cmd = copy_fd(tmp);
		if (tmp->type == TARGET)
			node->cmd = copy_fd(tmp);
		node->right = creat_right(tmp);
		if (node->right)
			node->right->father = node;
		node->left = creat_left(tmp);
		if (node->left)
			node->left->father = node;
	}
	return (node);
}
