/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:32 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/08 23:30:50 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include "io.h"

t_io	*new_io(int flag, int mode)
{
	t_io	*io;

	if (!(io = ft_memalloc(sizeof(t_io))))
		return (NULL);
	ft_bzero(io, sizeof(t_io));
	io->flag = flag;
	io->mode = mode;
	io->tab_fd[0] = -1;
	io->tab_fd[1] = -1;
	return (io);
}
