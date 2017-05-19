/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:14:59 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/10 17:25:20 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PARSER_H
# define LEXER_PARSER_H

typedef struct		s_token
{
	int				type;
	char			*word;
	int				select;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

enum				e_flag
{
	NO_QUOTE,
	S_QUOTE,
	D_QUOTE,
	OBT_QUOTE,
	BT_QUOTE
};

/*
**OBT_QUOTE : "$("
*/

/*
** Ne pas changer l'ordre des tokens please
*/

enum				e_token
{
	NO_TOKEN,
	CMD,
	ESPACE,
	DOT,
	PIPE,
	START,
	SL_DIR,
	SR_DIR,
	OR,
	AND,
	DL_DIR,
	DR_DIR,
	LR_DIR,
	DIR_L_AMP,
	DIR_R_AMP,
	FD_IN,
	TARGET,
	ARG
};

/*
** DOT,			";"
** PIPE,		'|"
** START,		"^, debut de ligne" -> utile ?
** SL_DIR,		"<"
** SR_DIR,		">"
** OR,			'||"
** AND,			'&&"
** DL_DIR,		"<<"
** DR_DIR,		">>"
** LR_DIR,		"<>"
** DIR_L_AMP,	"<&"
** DIR_R_AMP,	">&"
*/

typedef struct		s_cmd
{
	t_token			*prev_cmd;
	char			**cmd;
	int				in;
	int				out;
	struct s_cmd	*left;
	struct s_cmd	*right;
}					t_cmd;

t_token				*create_token();
void				push_token();
void				clear_token();
void				destroy_token();

int					can_create_tree(t_token	*lst);
int					is_end(char *s, int *i, char c);
int					find_quote_end(char *s);
int					is_end(char *s, int *i, char c);
t_token				*is_local_var(t_token *elem);

/*
** PAS IMPLEMENTEES
** t_cmd				*create_cmd();
** void				push_cmd();
** void				clear_cmd();
** void				destroy_cmd();
*/

#endif
