/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:15:28 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/03 21:15:28 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char *dst;

	if (((dst = (char*)malloc(sizeof(char) * (ft_strlen(s1) + 1))) == NULL))
		return (NULL);
	dst = ft_strcpy(dst, s1);
	return (dst);
}
