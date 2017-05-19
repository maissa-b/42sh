/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:20 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/08 23:30:49 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void		clean_pos_curs(void)
{
	if (g_curs.win_col >= (int)get_prompt_len())
	{
		g_curs.col = get_prompt_len();
		g_curs.row = 0;
	}
	else
	{
		g_curs.row = get_prompt_len() / g_curs.win_col;
		g_curs.col = get_prompt_len() % g_curs.win_col;
	}
}

t_bool		init_curs(void)
{
	if (get_win() == FALSE)
		return (FALSE);
	clean_pos_curs();
	return (TRUE);
}

int			get_curs(void)
{
	return (g_curs.win_col * g_curs.row + g_curs.col);
}

int			get_curs_add(int n)
{
	return (g_curs.win_col * g_curs.row + g_curs.col + n);
}
