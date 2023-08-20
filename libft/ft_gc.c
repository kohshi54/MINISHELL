#include "libft.h"
#include "ft_printf.h"

void	ft_free(void *ptr)
{
	// ft_printf("freed pointer %p\n", ptr);
	free(ptr);
}

void	*ft_malloc(size_t size, t_list **list)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	if (!(*list))
		*list = ft_lstnew(ptr);
	else
		ft_lstadd_back(list, ft_lstnew(ptr));
	// ft_printf("mallocated pointer %p\n", ptr);
	return (ptr);
}

void	free_all_mallocated_area(t_list *list)
{
	t_list	*tmplist;

	while (list)
	{
		tmplist = list;
		list = list->next;
		ft_lstdelone(tmplist, ft_free);
	}
}