/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:14:59 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/03 21:14:59 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# define OPEN	1
# define CLOSE	2
# define DUP	4
# define WRITE	8

typedef struct	s_io
{
	int			flag;
	int			mode;
	int			dup_src;
	int			dup_target;
	int			tab_fd[2];
	char		*str;
}				t_io;

typedef struct	s_mode
{
	int			redir;
	int			mode;
	int			flag;
}				t_mode;

typedef struct	s_redir
{
	char		*redir;
	int			mode;
}				t_redir;

t_io			*new_io();
char			*copy_redir(t_io *io);
char			*copy_process(t_process_p process);
char			*ft_fix_join(char *s, char *buf);
int				list_iter_int(t_list *list, int (*f)(void *, int), int d);
int				list_int2(t_list *list, int (*f)(void *, int, int),
				int d, int b);
int				apply_redir(t_io *io, int dofork);
int				restore_fd(t_io *io, int dofork);
int				is_builtin(char **args);
int				redir_open(t_io *io, int dofork);

/*
**	handle_jobs.c
*/

void			exec_simple_command(t_process_p p, int dofork);
int				shouldfork(t_job *j, t_list *pipeline);
void			do_pipeline(t_job *job, t_list *pipeline);
int				exec_pipeline(int last, t_job *j, t_node_p *current);
void			launch_job(t_job *j);

/*
**	handle_jobs2.c
*/

t_process_p		get_process_by_pid(pid_t pid);
t_job			*get_job_from_pid(pid_t pid);
int				mark_process_status(pid_t pid, int status, int *last);
int				job_is_complete(t_job *j);
int				wait_for_job(t_job *j);

/*
**	handle_jobs3.c
*/

void			launch_process(t_process_p process, int dofork);
t_node_p		iter_in_order(t_node_p ptr, t_list **stock);
void			do_pipe_in(t_io **io_in, int *io_pipe);
int				do_pipe(t_process_p p1, t_process_p p2, int *io_pipe);
int				make_children(t_process_p p);
int				save_fd(t_io *io, int type_redir, int dofork);

#endif
