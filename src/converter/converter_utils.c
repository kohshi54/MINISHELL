/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 19:16:30 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/07/08 19:16:53 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "converter.h"

char	*ft_strconnect(char *s1, char *s2, char *s3)
{
	size_t	len1;
	size_t	len2;
	size_t	len3;
	char	*ptr;

	if (!s1 || !s2 || !s3)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	ptr = ft_malloc(sizeof(char) * (len1 + len2 + len3 + 1), &ptr_list);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1, len1);
	ft_memcpy(ptr + len1, s3, len3);
	ft_memcpy(ptr + len1 + len3, s2, len2 + 1);
	return (ptr);
}

int	get_list_size(t_cmd_node *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return ((int)i);
}

bool	heredoc_exist(t_cmd_node *cmd)
{
	while (cmd)
	{
		if (cmd->kind == ND_REDIRECTION && ft_strncmp(cmd->str, "<<", 2) == 0)
		{
			return (true);
		}
		cmd = cmd->next;
	}
	return (false);
}

void	count_node2(t_node *cur, size_t *count)
{
	if (cur->left)
		count_node2(cur->left, count);
	if (cur->kind != ND_PIPE)
		(*count)++;
	if (cur->right)
		count_node2(cur->right, count);
}

size_t	get_node_count2(t_node *cur)
{
	size_t	count;

	count = 0;
	count_node2(cur, &count);
	return (count);
}
