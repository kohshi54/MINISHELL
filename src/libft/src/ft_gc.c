/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohshi54 <kohshi54@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:46:36 by tyonezaw          #+#    #+#             */
/*   Updated: 2023/11/13 07:49:57 by kohshi54         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_gc(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	*ft_malloc(size_t size, t_list **list)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_putstr_fd("fatal error: aborting process...\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (!(*list))
		*list = ft_lstnew(ptr);
	else
		ft_lstadd_back(list, ft_lstnew(ptr));
	return (ptr);
}

void	free_all_mallocated_area(t_list **list)
{
	t_list	*tmplist;

	while (*list)
	{
		tmplist = *list;
		*list = tmplist->next;
		ft_lstdelone(tmplist, free);
	}
	*list = NULL;
}