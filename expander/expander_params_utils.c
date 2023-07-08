/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_params_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:52:08 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/07/08 17:55:35 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_word	*append_new(t_word *prev, char *str, size_t num, int quote_flg, t_word **head)
{
	t_word	*cur;

	cur = ft_calloc(1, sizeof(t_word));
	cur->str = ft_strndup(str, num);
	cur->next = NULL;
	if (quote_flg == SINGLE)
		cur->in_single_quote = quote_flg;
	else
		cur->in_single_quote = 0;
	if (prev)
		prev->next = cur;
	else
		(*head) = cur;
	return (cur);
}

char	*ft_strjoin_null_accept(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*ptr;

	if (!s2)
		return (NULL);
	len1 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ptr = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1, len1);
	ft_memcpy(ptr + len1, s2, len2 + 1);
	return (ptr);
}

bool	is_env_assignable(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}

void	update_quote_flg(int *quote_flg, char c)
{
	if (*quote_flg == NONE && c == SINGLE_QUOTE)
		*quote_flg = SINGLE;
	else if (*quote_flg == NONE && c == DOUBLE_QUOTE)
		*quote_flg = DOUBLE;
	else if (*quote_flg == SINGLE && c == SINGLE_QUOTE)
		*quote_flg = NONE;
	else if (*quote_flg == DOUBLE && c == DOUBLE_QUOTE)
		*quote_flg = NONE;
}

char	*make_word(t_word *cur)
{
	char	*line;
	char 	*tmp;

	line = NULL;
	while (cur)
	{
		ft_printf("str: %s\n", cur->str);
		if (cur->in_single_quote == false && cur->str[0] == '$')
			cur->str = ft_getenviron(&(cur->str[1]));
		ft_printf("exp: %s\n", cur->str);
		if (cur->str)
		{
			tmp = line;
			line = ft_strjoin_null_accept(line, cur->str);
			// free(tmp);
			// free(cur->str);
		}
		cur = cur->next;
	}
	return (line);
}
