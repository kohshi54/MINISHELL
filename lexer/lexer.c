/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:11:22 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/07/05 19:15:54 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Breaks the input into words and operators, 
obeying the quoting rules described in Quoting.
These tokens are separated by metacharacters.
Alias expansion is performed by this step (see Aliases).

In minishell, quote and meta is applied.
*/

#include "lexer.h"

t_token	*execute_tokenize(t_token *cur, char *line)
{
	while (*line)
	{
		if (is_blank(*line))
		{
			skip_blank(&line);
			continue ;
		}
		if (is_operator(*line))
		{
			cur = make_operator_token(cur, &line);
			continue ;
		}
		if (is_word(*line))
		{
			cur = make_word_token(cur, &line);
			if (!cur)
				return (NULL);
			continue ;
		}
		ft_printf("minishell: unexpected token detected!\n");
		return (NULL);
	}
	cur = new_token(TK_EOF, cur, line, 1);
	return (cur);
}

t_token	*tokenize(char *line)
{
	t_token	head;
	t_token	*cur;

	cur = init_token(&head);
	cur = execute_tokenize(cur, line);
	if (!cur)
		return (NULL);
	return (head.next);
}
