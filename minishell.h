#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "$< "
# include <stdio.h>
# include "lexer/lexer.h"
# include "parser/parser.h"
# include "expander/expander.h"

char	*wrap_readline(char *str);
char	*ft_getenviron(char *key);

#endif