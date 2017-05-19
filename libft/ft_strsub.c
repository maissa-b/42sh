/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:15:31 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/03 21:15:31 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*new;
	size_t			i;

	i = 0;
	if (!s)
	{
		if (!(new = (char *)malloc(sizeof(char) * 1)))
			return (NULL);
	}
	else
	{
		if (!(new = (char *)malloc(sizeof(char) * (len + 1))))
			return (NULL);
	}
	while (s && s[start] && i < len)
	{
		new[i] = s[start];
		start++;
		i++;
	}
	new[i] = '\0';
	return (new);
}
