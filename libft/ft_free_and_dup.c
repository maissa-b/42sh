/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_and_dup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:15:22 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/03 21:15:22 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	dup src in dst then return dst, if dst already exists, dst is being free
*/

char		*ft_free_and_dup(char *dst, char *src)
{
	if (dst && dst[0])
		ft_strdel(&dst);
	dst = ft_strdup(src);
	return (dst);
}
