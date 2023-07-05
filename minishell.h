#ifndef MINISHELL_H
#define MINISHELL_H

#define PROMPT "$< "
#include <stdio.h>
#include "lexer/lexer.h"

char	*wrap_readline(char *str);
#endif