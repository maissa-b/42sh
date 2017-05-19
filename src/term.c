/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:35 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/11 17:51:59 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "read.h"

int			t_putchar(int i)
{
	write(1, &i, 1);
	return (0);
}

void		t_puts(char *s, int i)
{
	tputs(tgetstr(s, NULL), i, t_putchar);
}

t_term		*get_term(void)
{
	static t_term	term;

	return (&term);
}

int			init_termios(void)
{
	t_term			*st_term;

	st_term = get_term();
	if (!getenv("TERM") || ft_strcmp(getenv("TERM"), "xterm-256color"))
		tgetent(NULL, "xterm-256color");
	else if (tgetent(NULL, getenv("TERM")) < 1)
		return (-1);
	if (tcgetattr(0, &st_term->old) == -1)
		return (-1);
	if (tcgetattr(0, &st_term->new) == -1)
		return (-1);
	st_term->new.c_lflag &= ~(ICANON | ECHO | TOSTOP);
	st_term->new.c_cc[VMIN] = 1;
	st_term->new.c_cc[VDSUSP] = _POSIX_VDISABLE;
	st_term->new.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &st_term->new) == -1)
		return (-1);
	return (0);
}

int			close_termios(void)
{
	t_term			*st_term;

	st_term = get_term();
	if (tcsetattr(0, TCSADRAIN, &st_term->old) == -1)
	{
		return (-1);
	}
	return (0);
}
