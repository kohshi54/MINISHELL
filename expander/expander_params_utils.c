#include "expander.h"

t_word *append_new(t_word *prev, char *str, size_t num, int quote_flg)
{
	t_word *cur;

	cur = ft_calloc(1, sizeof(t_word));
	cur->str = ft_strndup(str, num);
	cur->next = NULL;
	if (quote_flg == SINGLE)
		cur->in_single_quote = quote_flg;
	else
		cur->in_single_quote = 0;
	prev->next = cur;
	return (cur);
}

char *ft_strjoin_null_accept(char *s1, char *s2)
{
	size_t len1;
	size_t len2;
	char *ptr;

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