/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_and_return.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:15:22 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/03 21:15:22 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	la fonction ft_free_and_return retourne l'int ret spécifié en argument
**	tout en liberant les pointeurs passés en parametre tant que NULL
**	n'est pas trouvé.
*/

int			ft_free_and_return(int ret, void *d1, void *d2, void *d3)
{
	(d1) ? ft_memdel(&d1) : 0;
	(d2) ? ft_memdel(&d2) : 0;
	(d3) ? ft_memdel(&d3) : 0;
	return (ret);
}
