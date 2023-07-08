#include "libft.h"

char	*ft_strndup_gc(const char *s1, size_t n, t_list **list)
{
	char	*p;
	char	*head;

	p = ft_malloc(sizeof(char) * (n + 1), list);
	if (!p)
		return (NULL);
	head = p;
	while (*s1 && n--)
		*p++ = *s1++;
	*p = '\0';
	return (head);
}