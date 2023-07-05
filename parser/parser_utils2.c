/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:02:57 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/07/05 20:03:05 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*init_new_node(void)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	new->str = NULL;
	new->left = NULL;
	new->right = NULL;
	new->cmd = NULL;
	new->kind = 0;
	return (new);
}

t_node	*create_left_node(t_token **token, t_node *root)
{
	t_node	*left;

	if (root != NULL)
		return (root);
	if (is_expected_token_left((*token)->kind) == false)
	{
		ft_printf("minishell: syntax error detected near '%s'!\n", \
					(*token)->str);
		return (NULL);
	}
	left = init_new_node();
	left->kind = ND_CMD;
	left->cmd = create_cmd_list(token);
	return (left);
}

t_node	*create_right_node(t_token **token)
{
	t_node	*right;

	if (is_expected_token_right((*token)->kind) == false)
	{
		ft_printf("minishell: syntax error detected near '%s'!\n", \
					(*token)->str);
		return (NULL);
	}
	right = init_new_node();
	right->kind = get_node_kind((*token)->kind);
	right->cmd = create_cmd_list(token);
	if (right->cmd == NULL)
		return (NULL);
	return (right);
}

t_node	*create_cur_node(t_token **token, t_node *root)
{
	t_node	*cur;

	cur = init_new_node();
	cur->left = create_left_node(token, root);
	if (!(cur->left))
		return (NULL);
	if (is_expected_token_cur((*token)->kind) == false)
	{
		ft_printf("minishell: syntax error detected near '%s'!\n", \
					(*token)->str);
		return (NULL);
	}
	cur->kind = ND_PIPE;
	cur->str = (*token)->str;
	(*token) = (*token)->next;
	cur->right = create_right_node(token);
	if (!(cur->right))
		return (NULL);
	return (cur);
}

t_cmd_node	*create_cmd_list(t_token **token)
{
	t_cmd_node	*head;
	t_cmd_node	*cur;
	t_cmd_node	*prev;

	head = NULL;
	prev = NULL;
	while ((*token) && (*token)->kind != TK_PIPE && (*token)->kind != TK_EOF)
	{
		if ((*token)->kind == TK_REDIRECTION && (*token)->next->kind != TK_WORD)
		{
			ft_printf("parse error: unexpected token in cmd\n");
			return (NULL);
		}
		cur = malloc(sizeof(t_cmd_node));
		if (!head)
			head = cur;
		cur->kind = get_node_kind((*token)->kind);
		cur->str = (*token)->str;
		if (prev)
			prev->next = cur;
		cur->next = NULL;
		prev = cur;
		*token = (*token)->next;
	}
	return (head);
}
