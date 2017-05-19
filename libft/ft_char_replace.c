/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:15:22 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/03 21:15:22 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_char_replace(char *s, char search, char replace)
{
	int		i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == search)
			s[i] = replace;
	}
	return (0);
}
