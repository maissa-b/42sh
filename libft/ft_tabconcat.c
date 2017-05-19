/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabconcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:15:31 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/03 21:15:31 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_tabconcat(char **tab)
{
	char	*concat;
	size_t	len;
	int		i;

	len = 0;
	i = -1;
	while (tab[++i])
	{
		len += ft_strlen(tab[i]);
	}
	if ((concat = ft_strnew(len + ft_tablen(tab))) == NULL)
		return (NULL);
	i = -1;
	while (tab[++i])
	{
		concat = ft_strcat(concat, tab[i]);
		concat[ft_strlen(concat)] = (tab[i + 1]) ? ' ' : '\0';
	}
	return (concat);
}
