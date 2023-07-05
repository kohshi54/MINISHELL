/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_split_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:25:01 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/07/05 21:25:42 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

bool	is_ifs(char c, char *ifs)
{
	while (*ifs)
	{
		if (c == *ifs)
			return (true);
		ifs++;
	}
	return (false);
}

char	*update_cur(char *old, char *line)
{
	return (ft_strndup(old, line - old));
}

t_cmd_node	*put_latter_into_new_node(char *line, t_cmd_node *old_next)
{
	t_cmd_node	*new;

	new = malloc(sizeof(t_cmd_node));
	new->kind = ND_CMD;
	new->str = ft_strdup(line);
	new->next = old_next;
	return (new);
}

void	split_node(t_cmd_node *cur, char *line, char *ifs)
{
	t_cmd_node	*tmp;

	cur->str = update_cur(cur->str, line);
	tmp = cur->next;
	while (is_ifs(*line, ifs) == true)
		line++;
	cur->next = put_latter_into_new_node(line, tmp);
}

void	split_node_when_presence_of_ifs(t_cmd_node *cur, char *ifs)
{
	char	*line;
	int		quote_flg;

	quote_flg = NONE;
	line = cur->str;
	while (line && *line)
	{
		if (quote_flg == NONE && *line == SINGLE_QUOTE)
			quote_flg = SINGLE;
		else if (quote_flg == NONE && *line == DOUBLE_QUOTE)
			quote_flg = DOUBLE;
		else if (quote_flg == SINGLE && *line == SINGLE_QUOTE)
			quote_flg = NONE;
		else if (quote_flg == DOUBLE && *line == DOUBLE_QUOTE)
			quote_flg = NONE;
		if (is_ifs(*line, ifs) == true && quote_flg == NONE)
		{
			split_node(cur, line, ifs);
			free(line);
			break ;
		}
		line++;
	}
}
