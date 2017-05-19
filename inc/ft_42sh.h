/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_42sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:14:59 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/10 21:54:59 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_42SH_H
# define FT_42SH_H

# include <stdlib.h>
# include <sys/syslimits.h>
# include "libft.h"
# include "options.h"
# include "completion.h"
# include "read.h"
# include "lexer_parser.h"
# include "lex.h"
# include "job.h"
# include "exec.h"
# include "globbing.h"
# include "builtins.h"
# include "history.h"

# define END_EOT	18

typedef _Bool t_bool;

typedef struct		s_elem
{
	char			*name;
	char			*value;
	unsigned int	is_appended;
	unsigned int	is_modified;
	struct s_elem	*next;
	struct s_elem	*prev;
}					t_elem;

typedef struct		s_lst
{
	size_t			size;
	t_elem			*head;
	t_elem			*tail;
}					t_lst;

typedef struct		s_core
{
	t_lst			*set;
	t_lst			*hist;
	t_lst			*env;
	t_lst			*exp;
	t_buf			*buf;
}					t_core;

typedef struct		s_builtin_array
{
	char			*cmd;
	int				(* const func)(t_core *, char **);
}					t_builtin_array;

/*
**	ft_default_set.c
*/
t_lst				*ft_init_lstset(void);

int					job_is_stopped (t_job *j);
int					job_is_completed(t_job *j);
void				continue_job (t_job *j, int foreground);
t_job				*ft_get_job(char *arg);
t_job				*get_last_job(void);
void				sigchld_handler(int sigchld);
void				init_signal(void);

/*
**	ft_init.c
*/
int					ft_init_core(void);
t_lst				*ft_default_env(void);
t_lst				*ft_init_list(void);
t_elem				*ft_init_elem(void);
char				**ft_env_to_tab(t_lst *lst);
t_lst				*ft_env_to_list(char **envp, t_lst *lst);

/*
**	ft_list_tools.c
*/
void				ft_print_lst(t_lst *lst);
void				ft_insert_elem(t_elem *elem, t_lst *lst);
int					ft_add_elem(t_lst *lst, char *s);
void				ft_del_elem(t_elem **elem, t_lst *lst);
t_elem				*ft_find_elem(char *name, t_lst *lst);
t_elem				*ft_new_elem(char *str);
void				ft_extract_elem(t_elem **elem, t_lst *lst);

/*
**	ft_list_tools2.c
*/
void				ft_lstclr(t_lst *lst);
t_elem				*ft_get_nelem(t_lst *lst, int n);
t_lst				*ft_lstcpy(t_lst *dst, t_lst *src);
t_elem				*ft_elemdup(t_elem *elem1);
t_lst				*ft_lstdup(t_lst *to_dup);

/*
**	ft_list.c
*/
int					ft_export(t_lst *dup, char *arg);
void				ft_exec(char **av);

/*
**	ft_norm_tools.c
*/
void				ft_del_list(t_lst *lst);
int					ft_pwd_swap(t_lst *env, char *owd, char *cwd);

void				block_signal(int sig, sigset_t *set, sigset_t *oset);
void				unblock_signal(sigset_t *oset);
void				restore_originals_handler();

t_term				*get_term(void);

void				ft_extract_elem(t_elem **elem, t_lst *lst);
void				ft_clear_elem(t_elem **elem);
void				ft_del_elem(t_elem **elem, t_lst *lst);

void				launch_job(t_job *j);
void				export_job(t_tree *root, t_list **g_job_list);
void				print_job_list(t_list *g_job_list);

int					parse_builtins(t_core *core, char *cmd, char **cmd_args);
int					up_shlvl(t_elem **elem);
int					ft_creat_core(char **envp);
void				get_sigwinch(int sig);

int					return_or_exit(char *error, int dofork);

#endif
