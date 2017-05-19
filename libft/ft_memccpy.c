/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:15:23 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/03 21:15:23 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (n > 0)
	{
		d[i] = s[i];
		if ((unsigned char)c == s[i])
		{
			d[i] = (unsigned char)c;
			return ((void *)d + i + 1);
		}
		n--;
		i++;
	}
	return (NULL);
}
