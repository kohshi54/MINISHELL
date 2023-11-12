/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gcaddft2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohshi54 <kohshi54@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:36:19 by tyonezaw          #+#    #+#             */
/*   Updated: 2023/11/13 07:50:52 by kohshi54         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_element(char const *s, char c)
{
	size_t	count;
	size_t	i;
	size_t	start;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		start = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (i == start)
		{
			i++;
			continue ;
		}
		count++;
		if (s[i] == '\0')
			return (count);
		i++;
	}	
	return (count);
}

char	**my_split_gc(const char *s, char c, char **p, t_list **list)
{
	size_t	i;
	size_t	count;
	size_t	start;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		start = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (i == start)
		{
			i++;
			continue ;
		}
		p[count] = ft_malloc(sizeof(char) * (i - start + 1), list);
		if (!p)
			return (NULL);
		ft_strlcpy(p[count++], &s[start], (i - start + 1));
		if (s[i++] == '\0')
			break ;
	}
	p[count] = NULL;
	return (&p[0]);
}

char	**ft_split_gc(char const *s, char c, t_list **list)
{
	char	**p;

	if (!s)
		return (NULL);
	p = ft_malloc(sizeof(char *) * (count_element(s, c) + 1), list);
	if (!p)
		return (NULL);
	p = my_split_gc(s, c, p, list);
	if (!p)
		return (NULL);
	return (p);
}

t_list	*ft_lstnew_gc(void *content, t_list **list)
{
	t_list	*ptr;

	ptr = ft_malloc(sizeof(t_list), list);
	if (!ptr)
		return (NULL);
	ptr->content = content;
	ptr->next = NULL;
	return (ptr);
}
