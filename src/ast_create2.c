/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:18 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/08 23:30:49 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
** fonction qui va chercher le bon element dans la list
** recursive lorsqu'il trouve plus d'element et que le bt
** ou bc lvl est incrementer
*/

t_token			*search_toke(t_token *lst)
{
	t_token	*tmp;
	t_token	*node_lst;

	tmp = lst;
	node_lst = NULL;
	if (lst == NULL)
		return (NULL);
	if (tmp->select == 1)
		tmp = tmp->next;
	while (tmp && tmp->select == 0)
	{
		if (priority(node_lst, tmp))
			node_lst = tmp;
		tmp = tmp->next;
	}
	return (node_lst);
}

/*
** remonte la liste
*/

t_token			*search_toke_prev(t_token *lst)
{
	t_token	*tmp;

	tmp = lst;
	if (lst == NULL)
		return (NULL);
	if (tmp->select == 1)
		tmp = tmp->prev;
	while (tmp && tmp->prev && tmp->select == 0)
		tmp = tmp->prev;
	return (search_toke(tmp));
}

/*
** cree le char **  ex: ls -la tmp
*/

void			cmd_len(t_token *lst, int *i, int *j)
{
	t_token	*tmp;
	int		tmpi;

	tmp = lst;
	tmpi = 0;
	while (tmp && (tmp->type == CMD || tmp->type == ARG))
	{
		if ((tmpi = ft_strlen(tmp->word)) >= *j)
			*j = tmpi;
		*i = *i + 1;
		tmp = tmp->next;
	}
}

char			**concate_cmd(t_token *lst)
{
	t_token	*tmp;
	int		i;
	int		j;
	int		count;
	char	**argv;

	tmp = lst;
	count = 0;
	i = 0;
	j = 0;
	cmd_len(tmp, &i, &j);
	argv = NULL;
	if (!(argv = (char **)malloc(sizeof(char*) * (i * j + 1))))
		return (NULL);
	argv[i * j] = NULL;
	while (tmp && tmp->word && (count <= i - 1))
	{
		argv[count] = ft_strdup(tmp->word);
		++count;
		tmp->select = 1;
		tmp = tmp->next;
	}
	argv[count] = NULL;
	return (argv);
}
