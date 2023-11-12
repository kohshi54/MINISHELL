/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohshi54 <kohshi54@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:12:41 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/11/13 07:02:15 by kohshi54         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "libft.h"
# include "lexer.h"
# include "parser.h"
# include "minishell.h"

/* expander_params.c */
char	*replace_params_to_value(char *line);
char	*convert_list_to_line(t_word *cur);
void	expand_params(t_node *cur);
t_node	*expand(t_node *root);

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '"'

/* expander_params_utils.c */
// t_word	*append_new(t_word *prev, char *str, size_t num, int single_quote_flg);
t_word	*append_new(t_word *prev, char *str, size_t num, int quote_flg, t_word **head);
char	*ft_strjoin_null_accept(char *s1, char *s2);
bool	is_env_assignable(char c);
void	update_quote_flg(int *quote_flg, char c);
char	*make_word(t_word *cur);

/* expander_split.c */
void	split_field(t_node *cur);

/* expander_split_utils.c */
void	split_node_when_presence_of_ifs(t_cmd_node *cur, char *ifs);

/* expander_removal.c */
typedef struct s_word2
{
	char			*str;
	struct s_word2	*next;
}	t_word2;

void	remove_quote(t_node *cur);

/* expander_removal_utils.c */
char	*removal(char *line);

#endif