#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_simplecmd
{
	struct s_redirect	*redirect;
	struct s_cmd		*cmd;
}	t_simplecmd;

# define PROMPT "$< "
# include <stdio.h>
# include "lexer/lexer.h"
# include "parser/parser.h"
# include "expander/expander.h"
# include "converter/converter.h"
# include "pipex/pipex.h"

char	*wrap_readline(char *str);
char	*ft_getenviron(char *key);

#endif