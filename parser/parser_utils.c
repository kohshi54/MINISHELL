/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:58:34 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/07/05 19:59:59 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	check_pipe_exist(t_token *token)
{
	while (token->kind != TK_EOF)
	{
		if (token->kind == TK_PIPE)
			return (true);
		token = token->next;
	}
	return (false);
}

t_node_kind	get_node_kind(t_token_kind kind)
{
	if (kind == TK_WORD)
		return (ND_CMD);
	if (kind == TK_PIPE)
		return (ND_PIPE);
	if (kind == TK_REDIRECTION)
		return (ND_REDIRECTION);
	return (ND_CMD);
}

bool	is_expected_token_left(t_token_kind kind)
{
	return (kind == TK_WORD || kind == TK_REDIRECTION);
}

bool	is_expected_token_right(t_token_kind kind)
{
	return (kind == TK_WORD || kind == TK_REDIRECTION);
}

bool	is_expected_token_cur(t_token_kind kind)
{
	return (kind == TK_PIPE);
}
