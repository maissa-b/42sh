/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:21 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/08 23:30:49 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**	ft_switch_path est une fonction appelé lorsque cd a 2 arguments
**	qui ne sont pas des options, afin de remplacer s1 dans s2.
*/

extern t_core *g_core;

char	*ft_switch_path(char *s1, char *s2)
{
	char		*path;
	char		*ptr;

	if ((path = ft_strnew(PATH_MAX)) == NULL)
		return (NULL);
	if ((getcwd(path, PATH_MAX)) == NULL)
		return (NULL);
	if ((ptr = ft_strstr(path, s1)) == NULL)
		ft_print_error(s1, ERR_STR_NOT_IN_PWD, ERR_NEW_CMD);
	else
	{
		if (path != NULL && path[0] != '\0')
		{
			if ((path = ft_concat_path(path, s1, s2, ft_strlen(ptr))) == NULL)
			{
				ft_strdel(&path);
				return (NULL);
			}
		}
	}
	return (path);
}

/*
**	ft_create_oldpath permet de creer un path a partir de l'OLDPWD
**	si il existe, sinon NULL est retourné.
*/

char	*ft_create_oldpath(char *f_path, t_lst *env)
{
	t_elem	*elem;

	elem = NULL;
	if ((elem = ft_find_elem("OLDPWD", env)) == NULL)
	{
		ft_print_error("cd -", ERR_OLDPWD_NOT_SET, ERR_NEW_CMD);
	}
	else
	{
		if (elem->value != NULL)
		{
			if ((f_path = ft_strdup(elem->value)) == NULL)
				return (NULL);
		}
		else
			ft_print_error("cd -", ERR_OLDPWD_NOT_SET, ERR_NEW_CMD);
	}
	return (f_path);
}

/*
**	fonction qui cree un path absolue en fonction de l'argument passé a cd,
**	appelé uniquement si l'argument ne contient pas de '/'.
*/

char	*ft_create_absolute_path(char *f_path, char *arg1)
{
	char	*cwd;
	t_elem	*elem;

	if ((f_path = ft_strnew(PATH_MAX)) != NULL)
	{
		cwd = getcwd(NULL, PATH_MAX);
		if (cwd)
		{
			f_path = ft_multi_concat(f_path, cwd, "/", arg1);
			ft_strdel(&cwd);
		}
		else
		{
			if ((elem = ft_find_elem("PWD", g_core->env)) && elem->value)
				f_path = ft_multi_concat(f_path, elem->value, "/", arg1);
		}
	}
	return (f_path);
}

/*
**	fonction qui check les arguments afin de savoir s'il est necessaire
**	de creer un path ou s'il suffit de renvoyer le path reçu
**	si ce dernier est absolu
*/

char	*ft_create_path2(t_lst *env, char *arg1)
{
	char	*f_path;

	f_path = NULL;
	if (ft_strcmp(arg1, "-") == 0)
	{
		if ((f_path = ft_create_oldpath(f_path, env)) == NULL)
		{
			return (NULL);
		}
	}
	else if (arg1[0] != '/')
	{
		if ((f_path = ft_create_absolute_path(f_path, arg1)) == NULL)
		{
			return (NULL);
		}
	}
	else
	{
		if ((f_path = ft_strdup(arg1)) == NULL)
		{
			return (NULL);
		}
	}
	return (f_path);
}

/*
**	definit si la fonction a appeler est celle remplacant arg1 par arg2
**	dans le pwd ou s'il faut creer un path a retourner.
*/

char	*ft_create_path(t_lst *env, char *arg1, char *arg2)
{
	char		*f_path;

	f_path = NULL;
	if (arg1 != NULL && (arg2 == NULL || arg2[0] == '\0'))
	{
		f_path = ft_create_path2(env, arg1);
	}
	else
	{
		f_path = ft_switch_path(arg1, arg2);
	}
	return (f_path);
}
