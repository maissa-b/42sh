/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:15:24 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/03 21:15:24 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_print_error(char *cmd, char *err, int ret)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, err, ft_strlen(err));
	write(2, "\n", 1);
	return (ret);
}
