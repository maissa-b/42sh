/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_jobs2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:31 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/08 23:30:50 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "io.h"
#include "job.h"
#include <errno.h>

extern	t_list	*g_job_list;
extern	t_core	*g_core;

t_process_p		get_process_by_pid(pid_t pid)
{
	t_list		*ptr_job;
	t_list		*ptr_process;
	t_job		*j;
	t_process_p	p;

	ptr_job = g_job_list;
	while (ptr_job)
	{
		j = ptr_job->content;
		ptr_process = j->wait_process_list;
		while (ptr_process)
		{
			p = ptr_process->content;
			if (p->pid == pid)
				return (p);
			ptr_process = ptr_process->next;
		}
		ptr_job = ptr_job->next;
	}
	return (NULL);
}

t_job			*get_job_from_pid(pid_t pid)
{
	t_list		*ptr_job;
	t_list		*ptr_process;
	t_job		*j;
	t_process_p	p;

	ptr_job = g_job_list;
	while (ptr_job)
	{
		j = ptr_job->content;
		ptr_process = j->wait_process_list;
		while (ptr_process)
		{
			p = ptr_process->content;
			if (p->pid == pid)
				return (j);
			ptr_process = ptr_process->next;
		}
		ptr_job = ptr_job->next;
	}
	return (NULL);
}

int				mark_process_status(pid_t pid, int status, int *last)
{
	t_process_p	p;

	if (pid > 0)
	{
		if ((p = get_process_by_pid(pid)))
		{
			p->status = status;
			get_job_from_pid(pid)->status = status;
			if (WIFSTOPPED(status))
				p->stopped = 1;
			else
			{
				p->completed = 1;
				*last = WEXITSTATUS(status);
			}
			return (0);
		}
		else
			return (-1);
	}
	else if (pid == 0 || errno == ECHILD)
		return (-1);
	else
		return (-1);
}

/*
** Check for processes that have status information available,
** blocking until all processes in the given job have reported.
*/

int				job_is_complete(t_job *j)
{
	t_process	*p;
	t_list		*ptr;

	ptr = j->wait_process_list;
	while (ptr)
	{
		p = ptr->content;
		if (!p->completed)
			return (0);
		ptr = ptr->next;
	}
	return (1);
}

int				wait_for_job(t_job *j)
{
	int			status;
	pid_t		pid;
	int			last;

	last = -1;
	(void)j;
	signal(SIGCHLD, SIG_DFL);
	while (true)
	{
		pid = waitpid(-1, &status, WUNTRACED);
		if ((mark_process_status(pid, status, &last)) || job_is_complete(j))
			break ;
	}
	return (last);
}
