/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_bang3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:20 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/08 23:30:49 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	*find_number(char *s)
{
	int		i;

	i = 0;
	if (s[0] == '-')
		i += 1;
	if (!ft_isdigit(s[i]))
		return (NULL);
	while (s[i])
	{
		if (s[i] > '9' || s[i] < '0')
			return (ft_strsub(s, 0, i));
		i++;
	}
	if (s[i - 1] < '9' && s[i - 1] > '0')
		return (ft_strdup(s));
	return (NULL);
}
