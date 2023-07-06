/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_removal_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:26:34 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/07/06 14:58:00 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*integrate_list_to_line(t_word2 *cur)
{
	char	*line;
	t_word2	*next;
	char	*tmp;

	line = NULL;
	while (cur)
	{
		if (cur->str)
		{
			tmp = line;
			line = ft_strjoin_null_accept(line, cur->str);
			free(tmp);
			free(cur->str);
		}
		next = cur->next;
		free(cur);
		cur = next;
	}
	return (line);
}

t_word2	*append_new_node(t_word2 *prev, char *str, size_t num)
{
	t_word2	*cur;
	char	*tmp;

	cur = ft_calloc(1, sizeof(t_word2));
	cur->str = ft_strndup(str, num);
	if (str[0] == SINGLE_QUOTE)
	{
		tmp = cur->str;
		cur->str = ft_strtrim(cur->str, "\'");
		free(tmp);
	}
	else if (str[0] == DOUBLE_QUOTE)
	{
		tmp = cur->str;
		cur->str = ft_strtrim(cur->str, "\"");
		free(tmp);
	}
	cur->next = NULL;
	if (prev)
		prev->next = cur;
	return (cur);
}

char	*sweep_line(char *line)
{
	int	quote_flg;

	quote_flg = NONE;
	while (*line)
	{
		if (quote_flg == NONE && *line == SINGLE_QUOTE)
			quote_flg = SINGLE;
		else if (quote_flg == NONE && *line == DOUBLE_QUOTE)
			quote_flg = DOUBLE;
		else if (quote_flg == SINGLE && *line == SINGLE_QUOTE)
		{
			line++;
			break ;
		}
		else if ((quote_flg == DOUBLE && *line == DOUBLE_QUOTE) \
				|| quote_flg == NONE)
		{
			line++;
			break ;
		}
		line++;
	}
	return (line);
}

char	*removal(char *line)
{
	t_word2	head;
	char	*start;
	t_word2	*cur;

	cur = &head;
	while (*line)
	{
		start = line;
		line = sweep_line(line);
		cur = append_new_node(cur, start, line - start);
	}
	return (integrate_list_to_line(head.next));
}
