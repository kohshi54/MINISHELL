/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:55:43 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/07/05 20:00:22 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The shell parses the input into simple commands and compound commands.

A "simple command" is 
a sequence of optional variable assignments and redirections,
in any sequence, 
optionally followed by words and redirections, terminated by a control operator.

In minishell, only simple commands is required.
The parser should work as follows:
Input: List of Tokens
Output: AST
*/

#include "parser.h"

t_node	*parse(t_token *cur)
{
	t_node	*root;

	root = NULL;
	while (cur && cur->kind != TK_EOF)
	{
		if (check_pipe_exist(cur) == true)
		{
			root = create_cur_node(&cur, root);
			if (!root)
				return (NULL);
		}
		else
		{
			root = create_right_node(&cur);
			if (!root)
				return (NULL);
		}
	}
	return (root);
}
