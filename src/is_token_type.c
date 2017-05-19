/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:33 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/08 23:30:50 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int			is_separator_type(int type)
{
	if (type == DOT || type == PIPE || type == OR || type == AND)
		return (1);
	return (0);
}

int			is_dir_type(int type)
{
	if (type == SR_DIR || type == DL_DIR || type == DR_DIR ||
	type == DIR_L_AMP || type == DIR_R_AMP || type == SL_DIR || type == LR_DIR)
		return (1);
	return (0);
}

int			is_text_type(int type)
{
	if (type == CMD || type == ARG || type == FD_IN || type == TARGET)
		return (1);
	return (0);
}
