/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:14:59 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/09 01:09:38 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_H
# define JOB_H
# include "list.h"
# include "ft_42sh.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <signal.h>

# define IS ==
# define TOKEN(x) (((t_tree *)x)->token)
# define DEF_FILE 0644

typedef struct s_node *t_node_p;

typedef enum		e_type_node
{
	PROCESS,
	IF
}					t_type_node;

# define BUILTIN 0x1
# define DOFORK 0x2
# define ALREADY_FORK 0x4
# define WAIT 0x8

typedef enum		e_type_if
{
	IF_OR,
	IF_AND
}					t_type_if;

typedef struct		s_node
{
	void			*data;
	size_t			size;
	t_type_node		type;
	t_node_p		left;
	t_node_p		right;
}					t_node;

typedef struct s_condition_if *t_condition_if_p;

typedef struct		s_condition_if
{
	t_type_if	type;
}					t_condition_if;

typedef struct s_process *t_process_p;

typedef struct		s_process
{
	int				token;
	int				flag;
	char			**argv;
	t_list			*io_list;
	pid_t			pid;
	char			completed;
	char			stopped;
	int				status;
}					t_process;

/*
** pid : process ID
** completed : true if process has completed
** stopped : true if process has stopped
** status : reported status value
*/

/*
**A job is a pipeline of processes.
*/

typedef struct		s_job
{
	int				status;
	char			*command;
	t_node_p		process_tree;
	char			notified;
	struct termios	s_term;
	int				flag;
	int				foreground;
	t_list			*wait_process_list;
}					t_job;

/*
** command : command line, used for messages
** process_tree : list of processes in this job
** pgid : process group ID
** notified : true if user told about stopped job
** s_term : saved terminal modes cf inc/read.h strcut s_term
** flag : mode exec
** foreground : foreground or background
*/

void				delete_job(t_job *j);

t_node_p			create_process(t_tree *node_process);
t_node_p			create_condition_if(t_tree *node_condition_if,
t_node_p right_node, t_node_p left_node);
t_node_p			create_pipe(t_node_p right_node, t_node_p left_node);
t_node_p			create_redir(t_tree *node_redir, t_node_p left_node);

char				*iter_cmd(t_node_p process_tree);
void				test_func(t_tree *root);

int					signal_dfl(void);
int					signal_ign(void);

void				do_job_notification(void);
void				format_job_info(t_job *job, const char *status);
t_node_p			create_redir(t_tree *node_redir, t_node_p left_node);
char				*iter_iolist_cmd(t_list *io_list);
int					ft_env_binary(char **args);

t_node_p			new_node(t_type_node type, size_t size);
void				*delete_node(t_node_p node);
void				*iter_pre_order(t_node_p node, t_list **stack);
void				delete_condition_if(t_condition_if_p condition_if);
void				delete_process(t_process_p process);
t_condition_if_p	new_condition_if(t_type_if type);

#endif
