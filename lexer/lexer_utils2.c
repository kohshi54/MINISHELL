/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:16:04 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/07/08 17:42:42 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*make_operator_token(t_token *cur, char **line)
{
	if (ft_strncmp(*line, "<<", 2) == 0)
	{
		cur = new_token(TK_REDIRECTION, cur, *line, 2);
		(*line) += 2;
	}
	else if (ft_strncmp(*line, ">>", 2) == 0)
	{
		cur = new_token(TK_REDIRECTION, cur, *line, 2);
		(*line) += 2;
	}
	else if (**line == '<' || **line == '>')
		cur = new_token(TK_REDIRECTION, cur, (*line)++, 1);
	else if (**line == '|')
		cur = new_token(TK_PIPE, cur, (*line)++, 1);
	return (cur);
}

t_token	*make_word_token(t_token *cur, char **line)
{
	char	*head;
	int		quote_flg;

	head = *line;
	quote_flg = NONE;
	while (**line && (!is_metacharacter(**line) || quote_flg))
	{
		if (quote_flg == NONE && **line == SINGLE_QUOTE)
			quote_flg = SINGLE;
		else if (quote_flg == NONE && **line == DOUBLE_QUOTE)
			quote_flg = DOUBLE;
		else if (quote_flg == SINGLE && **line == SINGLE_QUOTE)
			quote_flg = NONE;
		else if (quote_flg == DOUBLE && **line == DOUBLE_QUOTE)
			quote_flg = NONE;
		(*line)++;
	}
	if (quote_flg != NONE)
	{
		ft_printf("minishell: unclosed quote detected!\n");
		return (NULL);
	}
	cur = new_token(TK_WORD, cur, head, (*line) - head);
	return (cur);
}

t_token	*init_token(t_token *token)
{
	token->kind = 0;
	token->next = NULL;
	token->str = NULL;
	return (token);
}

t_token	*new_token(t_token_kind kind, t_token *prev, char *str, size_t num)
{
	t_token	*cur;

	// cur = ft_calloc(1, sizeof(t_token));
	cur = ft_malloc(sizeof(t_token), &ptr_list);
	cur->kind = kind;
	// cur->str = ft_strndup(str, num);
	cur->str = ft_strndup_gc(str, num, &ptr_list);
	prev->next = cur;
	return (cur);
}
