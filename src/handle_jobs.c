/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_jobs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:31 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/09 00:10:19 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "io.h"
#include "job.h"
#include <errno.h>

extern	t_list	*g_job_list;
extern	t_core	*g_core;

/*
** Store the status of the process pid that was returned by waitpid.
** Return 0 if all went well, nonzero otherwise.
*/

void			exec_simple_command(t_process_p p, int dofork)
{
	if (dofork)
		if (make_children(p))
			return ;
	launch_process(p, dofork);
}

int				shouldfork(t_job *j, t_list *pipeline)
{
	int			dofork;
	t_process_p	p;

	dofork = 0;
	p = pipeline->content;
	if (pipeline->next || !(p->flag & BUILTIN))
	{
		dofork = 1;
		j->flag = WAIT;
	}
	return (dofork);
}

void			do_pipeline(t_job *job, t_list *pipeline)
{
	int			io_pipe[2];
	int			fd_in_out[2];
	int			dofork;

	dofork = 0;
	fd_in_out[0] = STDIN_FILENO;
	dofork |= shouldfork(job, pipeline);
	while (pipeline)
	{
		list_int2(((t_process_p)pipeline->content)->io_list, (void *)save_fd,
			((t_process_p)pipeline->content)->token, dofork);
		fd_in_out[1] = (pipeline->next) ? do_pipe(pipeline->content,
		pipeline->next->content, io_pipe) : STDOUT_FILENO;
		exec_simple_command(pipeline->content, dofork);
		list_iter_int(((t_process_p)pipeline->content)->io_list,
			(void *)restore_fd, dofork);
		(fd_in_out[1] != STDOUT_FILENO) ? close(fd_in_out[1]) : 0;
		(fd_in_out[0] != STDIN_FILENO) ? close(fd_in_out[0]) : 0;
		fd_in_out[0] = io_pipe[0];
		delete_list(&(((t_process_p)pipeline->content)->io_list), &free);
		insert_link_bottom(&job->wait_process_list,
		new_link(ft_memcpy(malloc(pipeline->content_size), pipeline->content,
				pipeline->content_size), pipeline->content_size));
		pipeline = pipeline->next;
	}
}

int				exec_pipeline(int last, t_job *j, t_node_p *current)
{
	t_elem		*e;
	char		*s;

	s = NULL;
	do_pipeline(j, (*current)->data);
	(*current) = (*current)->right;
	last = wait_for_job(j);
	if (last >= 0)
	{
		if ((e = ft_find_elem("?", g_core->set)))
		{
			s = ft_itoa(last);
			if (e->value)
				e->value = ft_free_and_dup(e->value, s);
			else
				e->value = ft_strdup(s);
		}
		(s) ? free(s) : 0;
	}
	return (last);
}

void			launch_job(t_job *j)
{
	t_node_p	current;
	t_list		*stack;
	int			last;
	t_elem		*elem;

	last = 0;
	current = j->process_tree;
	stack = NULL;
	insert_link_bottom(&g_job_list, new_link(j, sizeof(t_job)));
	while ((current = iter_in_order(current, &stack)))
	{
		if (current->type == IF)
		{
			elem = ft_find_elem("?", g_core->set);
			last = ft_atoi(elem->value);
			current = ((((t_condition_if_p)current->data)->type == IF_OR &&
				last) || (((t_condition_if_p)current->data)->type == IF_AND &&
					!last)) ? current->right : NULL;
		}
		else
			last = exec_pipeline(last, j, &current);
	}
}
