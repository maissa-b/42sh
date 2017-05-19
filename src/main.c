/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:34 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/10 20:44:37 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

t_list	*g_job_list = NULL;
t_core	*g_core = NULL;
t_bool	g_is_here_doc;

static t_builtin_array g_builtin_array[] =
{
	{"cd", &ft_builtin_cd},
	{"env", &ft_builtin_env},
	{"setenv", &ft_builtin_setenv},
	{"unsetenv", &ft_builtin_unsetenv},
	{"exit", &ft_builtin_exit},
	{"echo", &ft_builtin_echo},
	{"history", &ft_builtin_history},
	{"unset", &ft_builtin_unset},
	{"export", &ft_builtin_export},
	{"loc", &ft_builtin_locale},
	{NULL, NULL}
};

/*
**	  init_core initialisation des liste d'env
*/

int			parse_builtins(t_core *core, char *cmd, char **cmd_args)
{
	int	i;

	i = -1;
	while (g_builtin_array[++i].cmd)
	{
		if (cmd)
		{
			if (ft_strncmp(g_builtin_array[i].cmd, cmd, ft_strlen(cmd)) == 0)
				return (g_builtin_array[i].func(core, cmd_args));
		}
	}
	return (1);
}

/*
**   si l'entree est different du terminal va lire ligne par ligne GNL
*/

static int	launch_execution(int ret, t_token *list)
{
	t_list	*job_list_bis;
	t_tree	*ast;

	job_list_bis = NULL;
	ast = NULL;
	if ((ret = ft_check_history_var(g_core)) == ERR_EXIT)
	{
		return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	}
	ft_push_ast(list, &ast);
	export_job(ast, &job_list_bis);
	list_iter(job_list_bis, (void *)launch_job);
	delete_list(&job_list_bis, NULL);
	free_ast(ast);
	return (ret);
}

static int	pre_core(t_buf **buf, t_completion *completion, char **envp)
{
	struct termios termio;

	g_is_here_doc = FALSE;
	tcgetattr(0, &termio);
	if (ft_creat_core(envp) == ERR_EXIT)
		return (ERR_EXIT);
	if (!(*buf = init_buf()))
		return (ft_print_error("42sh", ERR_MALLOC, ERR_EXIT));
	if (init_completion(completion, g_core) == ERR_EXIT)
		return (-1);
	if (!isatty(0))
		return (ft_print_error("42sh", " : Input not from a tty", ERR_NEW_CMD));
	set_prompt(PROMPT1, ft_strlen(PROMPT1));
	init_shell();
	g_core->buf = *buf;
	signal(SIGWINCH, get_sigwinch);
	g_curs.win_row = 0;
	g_curs.win_col = 0;
	g_curs.row = 0;
	g_curs.col = 0;
	init_curs();
	return (0);
}

static int	exec_core(int ret, t_completion *completion)
{
	int				ret_subs;
	t_token			*list;

	list = NULL;
	ret_subs = 0;
	if (is_line_ended(g_core->buf) < 0)
		return (-1);
	ret_subs = bang_substitution(&(g_core->buf->final_line), g_core);
	if (find_quote_end(g_core->buf->final_line) == TRUE
	&& ft_cmd_to_history(g_core->hist, g_core->buf->final_line) == ERR_EXIT)
		return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	ret = parse_buf(&list, g_core->buf->final_line, completion, g_core->hist);
	if (ret > 0 && list && ret_subs == 0)
		ret = launch_execution(ret, list);
	else if (ret_subs == 2)
		ft_putendl(g_core->buf->final_line);
	if (ret != ERR_NEW_PROMPT && g_core->buf->final_line)
		ft_strdel(&(g_core->buf->final_line));
	else
		complete_final_line(g_core->buf, list);
	(list) ? ft_tokendestroy(&list) : 0;
	ft_bzero(g_core->buf->line, BUFF_SIZE);
	g_core->buf->size = 0;
	clean_pos_curs();
	return ((init_completion(completion, g_core) == ERR_EXIT) ? -1 : ret);
}

int			main(int argc, char **argv, char **envp)
{
	t_completion	cplt;
	t_buf			*buf;
	int				ret;
	int				r;

	if (argc > 1)
		return (ft_print_error("42sh : cannot execute : ", argv[1], 0));
	cplt.hostname = NULL;
	cplt.command = NULL;
	cplt.username = NULL;
	cplt.variable = NULL;
	buf = NULL;
	if ((ret = pre_core(&buf, &cplt, envp)) < 0)
		return (ret);
	while ((r = read_line(g_core->buf, &cplt, g_core->hist)) != ERR_EXIT)
	{
		close_termios();
		if (r != TAB && r != ERR_NEW_CMD)
			ret = exec_core(ret, &cplt);
		if (r == END_EOT)
			break ;
	}
	close_termios();
	free_buf(g_core->buf);
	return (0);
}
