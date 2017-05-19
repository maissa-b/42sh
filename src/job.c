/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:33 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/09 01:06:04 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "list.h"
#include "io.h"

extern	t_list	*g_job_list;

int					iter_post_ord(t_tree **ptr, t_list **stock)
{
	while (*ptr)
	{
		if ((*ptr)->right)
			PUSH(stock, (*ptr)->right);
		PUSH(stock, *ptr);
		*ptr = (*ptr)->left;
	}
	*ptr = POP(stock);
	if (*stock && (*ptr)->right && TOP((*stock)) == (*ptr)->right)
	{
		POP(stock);
		PUSH(stock, *ptr);
		*ptr = (*ptr)->right;
		return (0);
	}
	return (1);
}

t_node_p			create_process_tree(t_tree *root)
{
	t_list	*stack;
	t_list	*stock;

	stock = NULL;
	stack = NULL;
	while (true)
	{
		if (iter_post_ord(&root, &stock))
		{
			if (TOKEN(root) == CMD)
				PUSH(&stack, create_process(root));
			else if ((TOKEN(root)) == OR || (TOKEN(root)) == AND)
				PUSH(&stack, create_condition_if(root, POP(&stack),
					POP(&stack)));
			else if (TOKEN(root) == PIPE)
				PUSH(&stack, create_pipe(POP(&stack), POP(&stack)));
			else if (is_dir_type(TOKEN(root)))
				PUSH(&stack, create_redir(root, POP(&stack)));
			root = NULL;
		}
		if (!stock)
			break ;
	}
	return (POP(&stack));
}

t_job				*create_job(t_tree *root, int foreground)
{
	t_job	*job;

	job = ft_memalloc(sizeof(t_job));
	ft_bzero(job, sizeof(t_job));
	job->foreground = foreground;
	job->process_tree = create_process_tree(root);
	return (job);
}

void				export_job(t_tree *root, t_list **job_list)
{
	while (root && TOKEN(root) == DOT)
	{
		insert_link_bottom(job_list, new_link(create_job(root->left,
			(TOKEN(root) == DOT) ? 1 : 0), sizeof(t_job)));
		root = root->right;
	}
	if (root)
		insert_link_bottom(job_list,
				new_link(create_job(root, 1), sizeof(t_job)));
}

t_condition_if_p	new_condition_if(t_type_if type)
{
	t_condition_if_p	ptr;

	ptr = malloc(sizeof(t_condition_if));
	ft_bzero(ptr, sizeof(t_condition_if));
	ptr->type = type;
	return (ptr);
}
