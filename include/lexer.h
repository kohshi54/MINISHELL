/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohshi54 <kohshi54@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:09:43 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/11/13 07:02:22 by kohshi54         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include "ft_printf.h"
# include "libft.h"
# include "minishell.h"

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