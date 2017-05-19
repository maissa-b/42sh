/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_and_join.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:15:22 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/03 21:15:22 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free_and_join(char *str1, char *str2)
{
	char	*tmp;

	tmp = NULL;
	if (str1 && str1[0])
	{
		tmp = ft_strdup(str1);
		ft_strdel(&str1);
	}
	str1 = ft_strjoin(tmp, str2);
	ft_strdel(&tmp);
	return (str1);
}
