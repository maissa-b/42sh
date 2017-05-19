/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_histopt_offset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:29 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/08 23:30:49 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int		ft_del_hist_offset(t_lst *hist, char *arg)
{
	t_elem	*tmp;
	int		offset;

	offset = ft_atoi(arg);
	if (offset <= 0 || offset > (int)hist->size)
	{
		ft_putstr_fd("history: ", 2);
		return (ft_print_error(arg, ": position out of range", ERR_NEW_CMD));
	}
	tmp = ft_get_nelem(hist, offset);
	ft_del_elem(&tmp, hist);
	return (0);
}

int		ft_histopt_d(t_lst *hist, char *arg)
{
	if (arg == NULL || *arg == '\0')
	{
		return (ft_print_error("history", ": usage -d <n>", ERR_NEW_CMD));
	}
	if (ft_del_hist_offset(hist, arg) == ERR_NEW_CMD)
	{
		return (ERR_NEW_CMD);
	}
	return (0);
}
