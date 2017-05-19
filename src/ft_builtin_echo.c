/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:21 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/09 20:23:08 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**	ft_builtin_echo est la seule fonction du builtin echo, elle gere
**	les erreurs, concat les arguments qu'elle reçoit en une string épurée
**	puis l'affiche.
*/

int		ft_builtin_echo(t_core *core, char **args)
{
	int		*opt;
	char	*tmp;
	char	*output;

	(void)core;
	if ((opt = ft_opt_parse(ECHO_OPTS, args, 0, 0)) == NULL)
		return (ERR_EXIT);
	if (opt[0] == -1)
		return (ft_free_and_return(ERR_NEW_CMD, opt, NULL, NULL));
	if (args && args[opt[0]])
	{
		if ((tmp = ft_tabconcat(args + opt[0])) == NULL)
			return (ft_free_and_return(ERR_EXIT, opt, NULL, NULL));
		if ((output = ft_epurstr(tmp)) == NULL)
			return (ft_free_and_return(ERR_EXIT, tmp, opt, NULL));
		write(1, output, ft_strlen(output));
		ft_multi_free(output, tmp, NULL, NULL);
	}
	if (opt[1] == 0)
		write(1, "\n", 1);
	free(opt);
	return (0);
}
