#include "minishell.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

char	*wrap_readline(char *str)
{
	char	*line;
	char	*prmpt;

	if (str)
		prmpt = str;
	else
		prmpt = PROMPT;
	line = readline(prmpt);
	if (line == NULL)
		exit (1);
	if (line[0] == '\0')
		return (line);
	if (!str)
		add_history(line);
	return (line);
}
