/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:15:29 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/07/08 19:11:14 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

/*
The '$' character is used to introduce parameter expansion, 
command substitution, or arithmetic evaluation.
If an unquoted '$' is followed by a character that is not one of the following:
・A numeric character
・The name of one of the special parameters (see Special Parameters)
・A valid first character of a variable name
・A <left-curly-bracket> ( '{' )
・A <left-parenthesis>

In minishell, only numeric character is considered.
*/

void	scan_param(char **line, int *quote_flg)
{
	(*line)++;
	while (is_env_assignable(**line) == true)
	{
		update_quote_flg(quote_flg, **line);
		(*line)++;
	}
}

void	scan_line(char **line, int *quote_flg)
{
	while (**line && **line != '$')
	{
		update_quote_flg(quote_flg, **line);
		(*line)++;
	}
}

char	*find_params_and_replace(char *line)
{
	t_word	*head;
	char	*start;
	t_word	*cur;
	int		quote_flg;

	cur = NULL;
	quote_flg = NONE;
	while (*line)
	{
		start = line;
		if (*line && *line == '$')
			scan_param(&line, &quote_flg);
		else
			scan_line(&line, &quote_flg);
		cur = append_new(cur, start, line - start, quote_flg, &head);
	}
	return (make_word(head));
}

void	execute_parameter_expansion(t_cmd_node *cur_cmd)
{
	char	*tmp;

	while (cur_cmd)
	{
		if (cur_cmd->kind == ND_REDIRECTION && \
			ft_strncmp(cur_cmd->str, "<<", 2) == 0)
		{
			if (cur_cmd->next)
			{
				cur_cmd = cur_cmd->next->next;
				continue ;
			}
		}
		tmp = cur_cmd->str;
		cur_cmd->str = find_params_and_replace(cur_cmd->str);
		cur_cmd = cur_cmd->next;
	}
}

void	expand_params(t_node *cur)
{
	if (cur->left)
		expand_params(cur->left);
	if (cur->kind != ND_PIPE)
		execute_parameter_expansion(cur->cmd);
	if (cur->right)
		expand_params(cur->right);
}
