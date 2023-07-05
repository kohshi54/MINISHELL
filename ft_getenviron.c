#include "minishell.h"

extern char	**environ;

void	*free_double(char **str)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (NULL);
}

char	*ft_getenviron(char *key)
{
	int		i;
	char	**str;
	char	*ret;

	i = 0;
	while (environ[i])
	{
		str = ft_split(environ[i], '=');
		if (ft_strncmp(str[0], key, ft_strlen(str[0])) == 0)
		{
			ret = ft_strdup(str[1]);
			free_double(str);
			return (ret);
		}
		free_double(str);
		i++;
	}
	return (NULL);
}
