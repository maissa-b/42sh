/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:29:11 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/10 21:54:17 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "io.h"
#include "job.h"

int			list_int2(t_list *list, int (*f)(void *, int, int), int d, int t)
{
	int		ret;

	while (list)
	{
		if ((ret = f(list->content, d, t)))
			return (ret);
		list = list->next;
	}
	return (0);
}

int			can_access(t_io *io)
{
	if (access(io->str, 0) == 0)
	{
		if (io->mode & O_SYMLINK && access(io->str, R_OK) == -1)
			return (FALSE);
		else if (io->mode & O_WRONLY && access(io->str, W_OK) == -1)
			return (FALSE);
		else if (io->mode & O_RDWR && access(io->str, R_OK | W_OK) == -1)
			return (FALSE);
	}
	return (TRUE);
}

int			redir_open(t_io *io, int dofork)
{
	struct stat	stat;

	lstat(io->str, &stat);
	if (S_ISDIR(stat.st_mode))
	{
		return (ft_print_error("42sh", ERR_IS_DIR,
			return_or_exit(ERR_IS_DIR, dofork)));
	}
	if (io->flag & CLOSE)
		io->dup_src = open(io->str, io->mode, DEF_FILE);
	if (can_access(io) == FALSE)
	{
		return (ft_print_error("42sh", ERR_NO_ACCESS,
			return_or_exit(ERR_NO_ACCESS, dofork)));
	}
	if (io->dup_src < 0)
	{
		return (ft_print_error("42sh", ERR_NO_FILE,
			return_or_exit(ERR_NO_FILE, dofork)));
	}
	return (0);
}

static int	check_close_fd(t_io *io, int dofork)
{
	if (io->dup_src > 2)
		close(io->dup_src);
	if (io->dup_target > 2)
		close(io->dup_target);
	if (io->tab_fd[0] > 2)
		close(io->tab_fd[0]);
	if (io->tab_fd[1] > 2)
		close(io->tab_fd[1]);
	return (ft_print_error("42sh", ERR_BADF,
		return_or_exit(ERR_BADF, dofork)));
}

int			apply_redir(t_io *io, int dofork)
{
	int		pipefd[2];
	int		ret;

	if (io->flag & OPEN)
	{
		if ((ret = redir_open(io, dofork)))
			return (ret);
	}
	if (io->flag & WRITE && pipe(pipefd) != -1)
	{
		io->dup_src = pipefd[0];
		write(pipefd[1], io->str, ft_strlen(io->str));
		close(pipefd[1]);
	}
	if (io->flag & DUP)
	{
		if ((io->tab_fd[0] == io->dup_src)
				|| (dup2(io->dup_src, io->dup_target) == -1 && dofork))
			return (check_close_fd(io, dofork));
	}
	if (io->flag & CLOSE && io->flag ^ WRITE && io->dup_target != io->dup_src)
		close(io->dup_src);
	return (0);
}
