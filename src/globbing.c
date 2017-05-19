/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 14:15:26 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/09 20:35:20 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int		globb(char **s, t_core *core, t_reg_path **new_args)
{
	int			i;
	int			ret;
	t_reg_path	*tmp;

	i = 0;
	ret = FALSE;
	if (*s[0] == '~' && replace_tild(s, core) == ERR_EXIT)
		return (ERR_EXIT);
	while (ret == FALSE)
	{
		is_end(*s, &i, '\'');
		if ((ret = replace_env_var(s, core)) == ERR_EXIT)
			return (ERR_EXIT);
		i++;
	}
	if ((tmp = replace_regex(*s)))
	{
		if (insert_new_args(s, new_args, tmp) == FALSE)
			return (FALSE);
	}
	else
		supp_quotes(*s);
	return (TRUE);
}

int		args_len(char **args, t_reg_path *reg_args)
{
	int			len;
	int			i;
	t_reg_path	*tmp;

	i = -1;
	len = 0;
	while (args[++i])
	{
		if (args[i][0])
			len += 1;
	}
	tmp = reg_args;
	while (tmp)
	{
		len += 1;
		tmp = tmp->next;
	}
	return (len);
}

char	**add_in_args(char **args, t_reg_path *reg_args)
{
	t_reg_path	*tmp;
	char		**new;
	int			i;
	int			j;

	if (!reg_args)
		return (args);
	if (!(new = ft_memalloc(sizeof(char *) * (args_len(args, reg_args) + 1))))
		return (NULL);
	i = -1;
	j = -1;
	while (args[++i])
		if (args[i][0] && !(new[++j] = ft_strdup(args[i])))
			return (NULL);
	tmp = reg_args;
	while (tmp)
	{
		if (tmp->out[0] && !(new[++j] = ft_strdup(tmp->out)))
			return (NULL);
		tmp = tmp->next;
	}
	new[j + 1] = NULL;
	return (new);
}

int		edit_cmd(char ***args, t_core *core)
{
	t_reg_path	*new_args;
	char		**tmp;
	int			i;

	new_args = NULL;
	i = -1;
	while ((*args)[++i])
	{
		if (globb(&(*args)[i], core, &new_args) == ERR_EXIT)
			return (ERR_EXIT);
	}
	if (new_args)
	{
		if (!(tmp = add_in_args(*args, new_args)))
			return (ERR_EXIT);
		*args = tmp;
		ft_reg_pathdestroy(&new_args);
	}
	return (0);
}
