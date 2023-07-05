#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*p;
	char	*head;

	p = malloc(sizeof(char) * (n + 1));
	if (!p)
		return (NULL);
	head = p;
	while (*s1 && n--)
		*p++ = *s1++;
	*p = '\0';
	return (head);
}