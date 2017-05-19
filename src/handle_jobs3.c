/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_jobs3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:31 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/08 23:39:18 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "io.h"
#include "job.h"
#include <errno.h>

extern	t_list	*g_job_list;
extern	t_core	*g_core;

void			launch_process(t_process_p process, int dofork)
{
	if (list_iter_int(process->io_list,
				(void *)apply_redir, dofork))
		return ;
	ft_check_exec(&process->argv);
	if (dofork)
		exit(1);
}

t_node_p		iter_in_order(t_node_p ptr, t_list **stock)
{
	while (ptr || *stock)
	{
		if (ptr)
		{
			PUSH(stock, ptr);
			ptr = ptr->left;
		}
		else
		{
			return (POP(stock));
		}
	}
	return (NULL);
}

void			do_pipe_in(t_io **io_in, int *io_pipe)
{
	io_in[0] = new_io();
	io_in[1] = new_io();
	io_in[0]->tab_fd[0] = dup(STDOUT_FILENO);
	io_in[0]->flag = DUP | CLOSE;
	io_in[1]->flag = CLOSE;
	io_in[0]->dup_src = io_pipe[1];
	io_in[0]->dup_target = STDOUT_FILENO;
	io_in[1]->dup_src = io_pipe[0];
}

int				do_pipe(t_process_p p1, t_process_p p2, int *io_pipe)
{
	t_io		*io_in[2];
	t_io		*io_out[2];

	if (pipe(io_pipe) == -1)
		exit(ft_print_error("42sh", ERR_PIPE, ERR_EXIT));
	do_pipe_in(io_in, io_pipe);
	io_out[0] = new_io();
	io_out[1] = new_io();
	io_out[0]->flag = DUP | CLOSE;
	io_out[1]->flag = CLOSE;
	io_out[0]->dup_src = io_pipe[0];
	io_out[0]->dup_target = STDIN_FILENO;
	io_out[1]->dup_src = io_pipe[1];
	PUSH(&(p1->io_list), io_in[0]);
	PUSH(&(p1->io_list), io_in[1]);
	PUSH(&(p2->io_list), io_out[0]);
	PUSH(&(p2->io_list), io_out[1]);
	return (io_pipe[1]);
}

int				make_children(t_process_p p)
{
	int			pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		signal(SIGCHLD, SIG_DFL);
	}
	else if (pid < 0)
		exit(ft_print_error("42sh", ERR_FORK, ERR_EXIT));
	else
		p->pid = pid;
	return (pid);
}
