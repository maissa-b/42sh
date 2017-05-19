/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_concat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:15:24 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/03 21:15:24 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_multi_concat(char *s1, char *s2, char *s3, char *s4)
{
	s1 = ft_strcat(s1, s2);
	s1 = ft_strcat(s1, s3);
	s1 = ft_strcat(s1, s4);
	return (s1);
}
