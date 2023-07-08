/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:09:43 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/07/08 17:42:02 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include "../libft/ft_printf.h"
# include "../libft/libft.h"
# include "../minishell.h"

typedef enum e_token_kind
{
	TK_WORD,
	TK_PIPE,
	TK_REDIRECTION,
	TK_EOF,
}	t_token_kind;

typedef struct s_token
{
	t_token_kind	kind;
	char			*str;
	struct s_token	*next;
}	t_token;

typedef enum e_quote_type
{
	NONE,
	SINGLE,
	DOUBLE,
}	t_quote_type;

/* lexer.c */
t_token	*tokenize(char *line);
t_token	*execute_tokenize(t_token *cur, char *line);

/* lexer_utils.c */
bool	is_metacharacter(char c);
bool	is_blank(char c);
bool	is_operator(char c);
void	skip_blank(char **line);
bool	is_word(char c);

/* lexer_utils2.c */
t_token	*new_token(t_token_kind kind, t_token *cur, char *str, size_t num);
t_token	*init_token(t_token *token);
t_token	*make_word_token(t_token *cur, char **line);
t_token	*make_operator_token(t_token *cur, char **line);

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '"'

#endif