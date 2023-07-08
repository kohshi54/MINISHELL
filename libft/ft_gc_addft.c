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

char	*ft_strjoin_gc(char const *s1, char const *s2, t_list **list)
{
	char	*p;
	char	*head;

	if (!s1 || !s2)
		return (NULL);
	p = ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 1, list);
	if (!p)
		return (NULL);
	head = p;
	while (*s1)
		*p++ = *s1++;
	while (*s2)
		*p++ = *s2++;
	*p = '\0';
	return (head);
}

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

char	**my_split_gc(const char *s, char c, char **p, size_t start, t_list **list)
{
	size_t	i;
	size_t	count;

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
		ft_strlcpy(p[count], &s[start], (i - start + 1));
		count++;
		if (s[i++] == '\0')
			break ;
	}
	p[count] = NULL;
	return (&p[0]);
}

char	**ft_split_gc(char const *s, char c, t_list **list)
{
	char	**p;
	size_t	start;

	start = 0;
	if (!s)
		return (NULL);
	p = ft_malloc(sizeof(char *) * (count_element(s, c) + 1), list);
	if (!p)
		return (NULL);
	p = my_split_gc(s, c, p, start, list);
	if (!p)
		return (NULL);
	return (p);
}
