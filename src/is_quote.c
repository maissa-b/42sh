/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:32 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/08 23:30:50 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int		is_dquote(char *s, int i)
{
	if (i == 0 || count_prev_char(s, i - 1, '\\') % 2 == 0)
	{
		if (s[i] == '"')
			return (1);
	}
	return (0);
}

int		is_squote(char *s, int i)
{
	if (i == 0 || count_prev_char(s, i - 1, '\\') % 2 == 0)
	{
		if (s[i] == '\'')
			return (1);
	}
	return (0);
}

int		find_dquote_end(char *s, int i)
{
	int	len;

	len = 0;
	if (i == 0 || count_prev_char(s, i - 1, '\\') % 2 == 0)
	{
		while (s[i + len])
		{
			if (is_dquote(s, i + len))
				break ;
			len++;
		}
		if (!s[i + len])
			return (-1);
		return (len);
	}
	return (0);
}

int		find_squote_end(char *s, int i)
{
	int	len;

	len = 0;
	if (i == 0 || count_prev_char(s, i - 1, '\\') % 2 == 0)
	{
		while (s[i + len])
		{
			if ((i + len == 0 || s[i + len - 1] != '\\') && s[i + len] == '\'')
				break ;
			len++;
		}
		if (!s[i + len])
			return (0);
		return (len);
	}
	return (0);
}

int		is_any_quote(char *s, int i)
{
	if (is_dquote(s, i) || is_squote(s, i))
		return (1);
	return (0);
}
