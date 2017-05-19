/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:15:44 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/03 21:15:44 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include "libft.h"
# include <fcntl.h>

typedef struct	s_str
{
	int			i;
	int			j;
	int			read;
	int			fd;
	char		*s;
}				t_str;

int				get_next_line(int const fd, char **line);

#endif
