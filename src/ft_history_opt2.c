/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_opt2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:29 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/08 23:30:49 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**	Print le message d'erreur des options invalides.
*/

int			ft_print_histopt_err(char c)
{
	ft_putstr_fd("history: ", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd(": invalid option \nhistory: usage: history [-c] \
[-d offset] [n] or history -awrn [filename] or history -ps arg [arg...]\n", 2);
	return (-1);
}

/*
**	Option c du builtin history, clear la liste hist si elle n'est pas NULL.
*/

t_lst		*ft_histopt_c(t_lst *hist)
{
	if (hist != NULL && hist->head != NULL && hist->size > 0)
	{
		ft_lstclr(hist);
	}
	return (hist);
}

/*
**	Ft_check_histopt_offset est une fonction qui gere les options prenant
**	un digit en parametre, ici seule l'option 'd' est concernee.
*/

int			ft_check_histopt_offset(t_lst *hist, char **args, int i)
{
	if (ft_histopt_d(hist, args[i + 1]) == ERR_NEW_CMD)
	{
		i = ERR_NEW_CMD;
	}
	else
	{
		i += 1;
	}
	return (i);
}
