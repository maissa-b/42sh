/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bang_special_sub.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:20 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/08 23:39:18 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int		bang_doll_sub(char *name, char **s)
{
	int		ret;
	char	*tmp;
	char	*tmp2;

	if ((tmp2 = ft_gets_lastword(name)) == NULL)
		return (ft_print_error("42sh: event not found: ", *s, -1));
	tmp = *s;
	ret = 0;
	if ((*s = ft_strreplace(tmp, "!$", tmp2)) == NULL)
		ret = ERR_NEW_CMD;
	(tmp2) ? ft_strdel(&tmp2) : 0;
	(tmp) ? ft_strdel(&tmp) : 0;
	return (ret);
}

int		dbang_sub(t_lst *hist, char **s)
{
	int		ret;
	char	*tmp;
	char	*tmp2;

	if ((tmp2 = ft_gets_lastcmd(hist)) == NULL)
		return (ft_print_error("42sh: event not found: ", *s, -1));
	tmp = *s;
	ret = 0;
	if ((*s = ft_strreplace(tmp, "!!", tmp2)) == NULL)
		ret = ERR_NEW_CMD;
	(tmp2) ? ft_strdel(&tmp2) : 0;
	(tmp) ? ft_strdel(&tmp) : 0;
	return (ret);
}

int		bang_wildcard_sub(char *name, char **s)
{
	int		ret;
	char	*tmp;
	char	*tmp2;

	if ((tmp2 = ft_gets_cmd_except_firstword(name)) == NULL)
		return (ft_print_error("42sh: event not found: ", *s, -1));
	tmp = *s;
	ret = 0;
	if ((*s = ft_strreplace(tmp, "!*", tmp2)) == NULL)
		ret = ERR_NEW_CMD;
	(tmp2) ? ft_strdel(&tmp2) : 0;
	(tmp) ? ft_strdel(&tmp) : 0;
	return (ret);
}

int		bang_diese_sub(char **s, int i)
{
	int		ret;
	char	*tmp;
	char	*tmp2;

	tmp = *s;
	if ((tmp2 = ft_gets_until_now(tmp, tmp + i - 1)) == NULL)
		return (ERR_EXIT);
	ret = 0;
	if ((*s = ft_strreplace(tmp, "!#", tmp2)) == NULL)
		ret = ERR_NEW_CMD;
	(tmp2) ? ft_strdel(&tmp2) : 0;
	(tmp) ? ft_strdel(&tmp) : 0;
	return (ret);
}
