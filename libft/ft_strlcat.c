/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:15:29 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/03 21:15:29 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int		ft_strlcat(char *dst, const char *src, unsigned int size)
{
	unsigned int	len_dst;
	unsigned int	i;

	len_dst = ft_strlen(dst);
	i = 0;
	if (size >= len_dst)
	{
		while (len_dst < size - 1)
		{
			dst[len_dst] = src[i];
			len_dst++;
			i++;
		}
		dst[len_dst] = '\0';
		return (len_dst + ft_strlen(src) - i);
	}
	return (ft_strlen(src) + size);
}
