/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:33 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/08 23:30:50 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

t_node_p	create_condition_if(t_tree *node_condition_if,
		t_node_p right_node, t_node_p left_node)
{
	t_node_p ptr;

	ptr = new_node(IF, sizeof(struct s_condition_if));
	ptr->left = left_node;
	ptr->right = right_node;
	ptr->data = new_condition_if((TOKEN(node_condition_if) == OR)
		? IF_OR : IF_AND);
	return (ptr);
}

t_node_p	create_pipe(t_node_p right_node, t_node_p left_node)
{
	insert_link_bottom((t_list **)&(left_node->data), right_node->data);
	delete_node(right_node);
	return (left_node);
}

void		*iter_pre_order(t_node_p node, t_list **stack)
{
	if (!node && !*stack)
		return (NULL);
	if (*stack)
		node = POP(stack);
	if (node->right)
		PUSH(stack, node->right);
	if (node->right)
		PUSH(stack, node->left);
	return (node);
}

void		delete_condition_if(t_condition_if_p condition_if)
{
	if (!condition_if)
		return ;
	free(condition_if);
}

void		delete_process(t_process_p process)
{
	if (!process)
		return ;
	if (process->io_list)
		delete_list(&(process->io_list), &free);
	free(process);
}
