/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:34 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/08 23:30:51 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

t_prompt	manage_prompt(char *s, int num)
{
	static t_prompt	prompt;

	if (s)
		prompt.s = s;
	if (num)
		prompt.len = num;
	return (prompt);
}

char		*get_prompt_str(void)
{
	return (manage_prompt(NULL, 0).s);
}

void		set_prompt(char *s, int len)
{
	manage_prompt(s, len);
}

size_t		get_prompt_len(void)
{
	return ((size_t)manage_prompt(NULL, 0).len);
}
