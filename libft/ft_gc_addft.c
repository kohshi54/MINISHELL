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

char	*ft_strdup_gc(const char *s1, t_list **list)
{
	char	*p;

	p = ft_malloc(sizeof(char) * ft_strlen(s1) + 1, list);
	if (!p)
	{
		errno = ENOMEM;
		return (NULL);
	}
	ft_strlcpy(p, s1, ft_strlen(s1) + 1);
	return (p);
}

static bool	check(char s1, char const *set)
{
	while (*set)
		if (s1 == *set++)
			return (1);
	return (0);
}

char	*ft_strtrim_gc(char const *s1, char const *set, t_list **list)
{
	size_t	i;
	size_t	j;
	char	*p;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (check(s1[i], set))
		i++;
	j = ft_strlen(s1) - 1;
	while (check(s1[j], set) && (i < j))
		j--;
	p = ft_malloc(sizeof(char) * (j - i + 2), list);
	if (!p)
		return (NULL);
	ft_strlcpy(p, &s1[i], (j - i + 2));
	return (p);
}
