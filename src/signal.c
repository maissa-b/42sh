/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:35 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/09 23:27:28 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_core	*g_core;
extern t_bool	g_is_here_doc;

t_bool		get_win(void)
{
	struct winsize	windows;
	int				len;

	len = get_curs_add(-(get_prompt_len()));
	if (ioctl(0, TIOCGWINSZ, &windows) < 0)
		return (FALSE);
	if ((g_curs.win_col * g_curs.row) + g_curs.col >= (int)get_prompt_len())
	{
		t_puts("cl", 1);
		ft_putstr_fd(get_prompt_str(), 1);
	}
	g_curs.win_col = windows.ws_col;
	g_curs.win_row = windows.ws_row;
	clean_pos_curs();
	print_post_curs(g_core->buf);
	m_right(len);
	return (TRUE);
}

void		get_sigwinch(int sig)
{
	if (sig == SIGWINCH)
		get_win();
	return ;
}

void		get_sigint(int sig)
{
	if (sig == SIGINT)
	{
		m_right(calc_len(g_core->buf, END));
		g_core->buf->size = 0;
		ft_bzero(g_core->buf->line, BUFF_SIZE);
		ft_strdel(&(g_core->buf->final_line));
		set_prompt(PROMPT1, ft_strlen(PROMPT1));
		clean_pos_curs();
		ft_putchar_fd('\n', 1);
	}
	return ;
}
