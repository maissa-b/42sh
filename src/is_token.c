/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:33 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/09 20:50:01 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int		count_prev_char(char *s, int i, char c)
{
	int len;

	if (i >= (int)ft_strlen(s))
		return (0);
	len = 0;
	while (i - len >= 0 && s[i - len] == c)
	{
		len += 1;
	}
	return (len);
}

int		is_char(char *s, int i, char c)
{
	if (i == 0 || count_prev_char(s, i - 1, '\\') % 2 == 0)
	{
		if (s[i] == c)
			return (1);
	}
	return (0);
}

int		find_prev_char(char *s, int len, char c)
{
	int		i;

	i = 0;
	while (len - i > 0)
	{
		if (is_char(s, len - i, c))
			return (i);
		i++;
	}
	return (0);
}

int		find_next_char(char *s, int len, char c)
{
	int		i;

	i = 0;
	while (len + i < (int)ft_strlen(s))
	{
		if (is_char(s, len + i, c))
			return (i);
		i++;
	}
	return (-1);
}

int		is_cmd(char *s, int i)
{
	while (i >= 0 && (is_char(s, i, ' ') || is_any_quote(s, i)))
		i--;
	if (i < 0)
		return (1);
	if (i >= 0 && is_separator(s, i))
		return (1);
	return (0);
}
