/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:54:24 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/07/08 18:06:22 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

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
