/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:15:23 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/09 15:15:20 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_is_valid_dir(const char *dirname)
{
	DIR			*dir;
	struct stat st;

	dir = NULL;
	ft_bzero(&st, sizeof(st));
	lstat(dirname, &st);
	if (S_ISDIR(st.st_mode) || S_ISLNK(st.st_mode))
	{
		if ((dir = opendir(dirname)))
		{
			closedir(dir);
			return (0);
		}
		return (ft_print_error((char *)dirname, ERR_NO_ACCESS, ERR_NEW_CMD));
	}
	else
	{
		return (ft_print_error((char *)dirname, ERR_NO_FILE, ERR_NEW_CMD));
	}
}
