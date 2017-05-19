/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:28 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/10 17:59:54 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
** decoupe la path pour effectue l'execution du binaire dans chaque dossier
*/

extern t_core	*g_core;

static char		*ft_cut_path(char **s, char *av)
{
	char		*s1;
	char		*s2;
	char		*tmp;
	int			i;

	i = 0;
	s1 = *s;
	while (s1[i] && s1[i] != ':')
		i++;
	s2 = ft_memalloc(sizeof(char) * (i + 2 + ft_strlen(av)));
	ft_strncpy(s2, s1, i);
	ft_strncpy(s2 + i, "/", 1);
	ft_strncpy(s2 + i + 1, av, ft_strlen(av));
	if (s1[i] && s1[i] == ':')
		i++;
	tmp = ft_strdup(s1 + i);
	s1 = NULL;
	ft_strdel(s);
	*s = tmp;
	return (s2);
}

/*
** fonction d'execution des commandes via execve
** lstat verifie l'authorisation d'execution
*/

void			not_binary(char *s, char *s2, char **av, char **envp)
{
	struct stat	st;

	if (ft_strchr(av[0], '/') && lstat(av[0], &st) == 0 &&
	st.st_mode & S_IXUSR && access(av[0], X_OK) == 0)
		execve(av[0], av, envp);
	if (s2 && lstat(s2, &st) == 0 && st.st_mode & S_IXUSR
			&& access(s2, X_OK) == 0)
		execve(s2, av, envp);
	if (!s || ft_strcmp(s, "") == 0)
	{
		(s) ? free(s) : 0;
		(s2) ? free(s2) : 0;
		(envp) ? ft_tabdel(envp) : 0;
		if (lstat(av[0], &st) == 0 && st.st_mode & S_IXUSR)
			ft_putstr_fd("42sh: exec format error: ", 2);
		else if (lstat(av[0], &st) == 0)
			ft_putstr_fd("42sh: permission denied: ", 2);
		else if (!s)
			ft_putstr_fd("42sh: no such file or directory: ", 2);
		else
			ft_putstr_fd("42sh: command not found: ", 2);
		ft_putendl_fd(av[0], 2);
		exit(1);
	}
}

/*
** recuperer l'env pour execve
** remplace le path pour l'envoie a execve
*/

void			ft_exec(char **av)
{
	char		*s;
	char		*s2;
	char		**envp;
	t_elem		*tmp;

	s2 = NULL;
	envp = ft_env_to_tab(g_core->env);
	tmp = ft_find_elem("PATH", g_core->env);
	s = (!tmp || !tmp->value) ? ft_strdup("") : ft_strdup(tmp->value);
	if (av && av[0] && av[0][0] && ((av[0][0] == '.' && av[0][1] == '/') ||
			(av[0][0] == '/')))
		not_binary(NULL, NULL, av, envp);
	while (true)
	{
		s2 = ft_cut_path(&s, av[0]);
		not_binary(s, s2, av, envp);
		(s2) ? ft_strdel(&s2) : 0;
		if (!s)
			break ;
	}
	(s) ? free(s) : 0;
	(s2) ? free(s2) : 0;
	(envp) ? ft_tabdel(envp) : 0;
	exit(1);
}

/*
** edit_cmd remplace la commande avec la completion
** sert a retourner si la cmd c'est un builtin
*/

int				ft_check_exec(char ***cmd)
{
	t_elem		*e;
	int			ret;
	char		*s;

	s = NULL;
	ret = TRUE;
	if (edit_cmd(cmd, g_core) == ERR_EXIT)
		return (ERR_EXIT);
	if (**cmd && (ret = parse_builtins(g_core, *cmd[0], *cmd + 1)) == 1)
		ft_exec(*cmd);
	else
	{
		if ((e = ft_find_elem("?", g_core->set)))
		{
			s = ft_itoa((ret < 0) ? ret * -1 : ret);
			if (e->value)
				e->value = ft_free_and_dup(e->value, s);
			else
				e->value = ft_strdup(s);
		}
		(s) ? free(s) : 0;
	}
	return (ret);
}
