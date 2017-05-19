/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:21 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/09 01:53:41 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	ft_del_core(t_core *core)
{
	if (core)
	{
		if (core->set)
			ft_del_list(core->set);
		if (core->exp)
			ft_del_list(core->exp);
		if (core->env)
		{
			ft_del_list(core->env);
		}
		if (core->hist)
			ft_del_list(core->hist);
		ft_memdel((void*)&core);
	}
}

/*
**	la fonction ft_builtin_exit gere les erreurs des arguments (s'il y en a),
**	retourne -1 comme tout builtin si une erreur occure, sinon exit est appelé
**	soit avec 0 (si aucun arguments n'est présent), ou la valeur numeric
**	contenu dans args[0] (plus d'arguments provoque une erreur).
*/

int		ft_builtin_exit(t_core *core, char **args)
{
	int	ret;

	ret = 0;
	if (args && args[0])
	{
		if (!is_number(args[0], ft_strlen(args[0])) || args[1])
			return (ft_print_error("exit", ERR_EXPR_SYNT, ERR_NEW_CMD));
		else if (!ft_strisdigit(args[0]) && args[0][0] != '-')
			return (ft_print_error("exit", ERR_EXT_FRMT, ERR_NEW_CMD));
		ret = (unsigned char)ret;
		ret = ft_atoi(args[0]);
	}
	ft_histopt_w(core, NULL);
	ft_check_history_var(core);
	ft_del_core(core);
	clean_pos_curs();
	close_termios();
	exit(ret);
	return (ret);
}
