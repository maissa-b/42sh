/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:22 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/10 20:16:33 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**    va suprimmer un variable dans n'importe quel list
*/

int		ft_unset(t_core *set, char **args)
{
	while (*args != NULL)
	{
		if (ft_strchr(*args, '=') != NULL || !ft_isalpha(*args[0]))
			ft_print_error("unset: Not a valid identifier: ", *args, -1);
		else
		{
			if (ft_unsetenv(set->exp, *args) != 1)
				if (ft_unsetenv(set->set, *args) != 1)
					ft_unsetenv(set->env, *args);
		}
		args++;
	}
	return (0);
}

int		ft_builtin_unset(t_core *set, char **args)
{
	int	*opt;
	int	ret;

	if (args == NULL || *args == NULL || **args == '\0')
		return (0);
	if ((opt = ft_opt_parse(UNSET_OPT, args, 0, 0)) == NULL)
		return (ERR_EXIT);
	ret = (opt[0] < 0) ? opt[0] : ft_unset(set, args + opt[0]);
	free(opt);
	return (ret);
}
