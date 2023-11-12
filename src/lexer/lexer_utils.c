/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:13:48 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/07/05 19:18:16 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
@token
A sequence of characters considered a single unit by the shell.
It is either a word or an operator.

@word
A sequence of characters treated as a unit by the shell.
Words may not include unquoted metacharacters.

@operator
A control operator or a redirection operator.
See Redirections, for a list of redirection operators.
Operators contain at least one unquoted metacharacter.

@control operator
A token that performs a control function.
It is a newline or one of the following:
‘||’, ‘&&’, ‘&’, ‘;’, ‘;;’, ‘;&’, ‘;;&’, ‘|’, ‘|&’, ‘(’, or ‘)’.
(In minishell, it is defined as follows: A control operator is a '|'.)

@metacharacter
A character that, when unquoted, separates words.
A metacharacter is a space, tab, newline,
or one of the following characters: ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’.
(In minishell, it is defined as follows:
A metacharacter is a space, tab, newline, ‘|’, ‘<’, or ‘>’.)

@blank
A space or tab character.
*/

#include "lexer.h"

bool	is_metacharacter(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' \
			|| c == '|' || c == '<' || c == '>');
}

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

bool	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	skip_blank(char **line)
{
	while (**line && is_blank(**line))
		(*line)++;
}

bool	is_word(char c)
{
	return (c && !is_metacharacter(c));
}
