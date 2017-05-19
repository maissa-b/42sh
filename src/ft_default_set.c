/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_default_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:28 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/08 23:30:49 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
** env par defaut
*/

t_lst	*ft_default_env(void)
{
	t_lst	*env;
	char	*pwd;

	pwd = NULL;
	if (!(env = ft_init_list()))
		return (NULL);
	if (!(pwd = getcwd(NULL, PATH_MAX)))
	{
		ft_memdel((void*)&env);
		return (NULL);
	}
	ft_setenv(env, "PWD", pwd);
	ft_setenv(env, "SHLVL", "2");
	ft_setenv(env, "_", NULL);
	ft_strdel(&pwd);
	return (env);
}

/*
**	ft_init_lstset est une fonction qui va initialiser la liste du set
**	avec les variables HISTFILE, HISTSIZE et HISTFILESIZE, définis sur
**	les standards de bash.
*/

t_lst	*ft_init_lstset(void)
{
	t_lst	*set;
	char	*pwd;
	char	*histfilepath;

	pwd = NULL;
	histfilepath = NULL;
	set = NULL;
	if ((set = ft_init_list()) == NULL)
		return (NULL);
	if ((pwd = getcwd(NULL, PATH_MAX)) == NULL)
	{
		free(set);
		return (NULL);
	}
	if ((histfilepath = ft_strnew((ft_strlen(pwd) + 18))) == NULL)
		return (NULL);
	ft_strcpy(histfilepath, pwd);
	histfilepath = ft_strcat(histfilepath, "/.ft_42sh_history");
	ft_setenv(set, "HISTFILE", histfilepath);
	ft_multi_free(pwd, histfilepath, NULL, NULL);
	ft_setenv(set, "HISTSIZE", "500");
	ft_setenv(set, "HISTFILESIZE", "500");
	ft_add_elem(set, "?=0");
	return (set);
}
