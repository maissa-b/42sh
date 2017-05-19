/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_local_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:32 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/08 23:30:50 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int			is_var_val(char *s)
{
	int		i;
	int		s_len;

	i = -1;
	s_len = ft_strlen(s);
	while (++i < s_len)
	{
		is_end(s, &i, '\'');
		is_end(s, &i, '"');
		if (i < s_len && s[i] == '=')
			return (TRUE);
	}
	return (FALSE);
}

t_token		*insert_env_export_in_list(t_token *tmp, t_token *lst)
{
	t_token	*new;
	char	*cmd;

	if (tmp && is_text_type(tmp->type))
		cmd = "env";
	else
		cmd = "export";
	if (!(new = ft_tokenew(CMD, ft_strdup(cmd))))
		return (NULL);
	lst->type = ARG;
	if (lst->prev)
		lst->prev->next = new;
	new->prev = lst->prev;
	lst->prev = new;
	new->next = lst;
	return (new);
}

t_token		*is_local_var(t_token *lst)
{
	t_token	*tmp;
	int		n_tmp;
	int		ret;

	n_tmp = 0;
	tmp = lst;
	if (!ft_strchr(lst->word, '='))
		return (lst);
	while (tmp)
	{
		if (!(ret = is_var_val(tmp->word)))
			break ;
		tmp = tmp->next;
		n_tmp++;
	}
	if (n_tmp == 0 && ret == FALSE)
		return (lst);
	return (insert_env_export_in_list(tmp, lst));
}
