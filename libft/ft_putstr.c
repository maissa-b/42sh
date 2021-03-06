/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:15:27 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/03 21:15:27 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_putstr(const char *s)
{
	unsigned int	i;

	i = ft_strlen(s);
	write(1, s, i);
}
