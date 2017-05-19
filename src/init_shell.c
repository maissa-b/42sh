/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:32 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/08 23:30:50 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void		init_signal(void)
{
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void		init_shell(void)
{
	struct sigaction act;

	ft_memset(&act, '\0', sizeof(act));
	act.sa_flags = 0;
	act.sa_handler = &get_sigint;
	sigaction(SIGINT, &act, NULL);
	init_signal();
}
