/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:54:24 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/07/06 15:04:37 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../lexer/lexer.h"

typedef enum e_node_kind
{
	ND_CMD,
	ND_PIPE,
	ND_REDIRECTION,
}	t_node_kind;

typedef struct s_arg_node
{
	char				*str;
	struct s_arg_node	*next;
}	t_arg_node;

typedef struct s_cmd_node
{
	t_node_kind			kind;
	char				*str;
	struct s_cmd_node	*next;
}	t_cmd_node;

typedef struct s_node
{
	t_node_kind		kind;
	char			*str;
	struct s_node	*left;
	struct s_node	*right;
	t_cmd_node		*cmd;
}	t_node;

extern char	**environ;

/* parser.c */
t_node		*parse(t_token *token);

/* parser_utils.c */
bool		check_pipe_exist(t_token *token);
t_node_kind	get_node_kind(t_token_kind kind);
bool		is_expected_token_left(t_token_kind kind);
bool		is_expected_token_right(t_token_kind kind);
bool		is_expected_token_cur(t_token_kind kind);

/* parser_utils2.c */
t_node		*init_new_node(void);
t_node		*create_left_node(t_token **token, t_node *root);
t_node		*create_right_node(t_token **token);
t_node		*create_cur_node(t_token **token, t_node *root);
t_cmd_node	*create_cmd_list(t_token **token);

#endif
