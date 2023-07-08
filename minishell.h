#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>

/* lexer */
typedef enum e_token_kind
{
	TK_WORD,
	TK_PIPE,
	TK_REDIRECTION,
	TK_EOF,
}	t_token_kind;

typedef struct s_token
{
	t_token_kind	kind;
	char			*str;
	struct s_token	*next;
}	t_token;

typedef enum e_quote_type
{
	NONE,
	SINGLE,
	DOUBLE,
}	t_quote_type;

/* parser */
typedef enum e_node_kind
{
	ND_CMD,
	ND_PIPE,
	ND_REDIRECTION,
}	t_node_kind;

typedef struct s_arg_node
{
	char				*str;
	struct s_arg_node	*next;
}	t_arg_node;

typedef struct s_cmd_node
{
	t_node_kind			kind;
	char				*str;
	struct s_cmd_node	*next;
}	t_cmd_node;

typedef struct s_node
{
	t_node_kind		kind;
	char			*str;
	struct s_node	*left;
	struct s_node	*right;
	t_cmd_node		*cmd;
}	t_node;

/* expander */
typedef struct s_word
{
	char			*str;
	bool			in_single_quote;
	struct s_word	*next;
}	t_word;



typedef struct s_simplecmd
{
	struct s_redirect	*redirect;
	struct s_cmd		*cmd;
}	t_simplecmd;

# define PROMPT "$< "
# include <stdio.h>
# include "libft/libft.h"
t_list	*ptr_list;
# include "lexer/lexer.h"
# include "parser/parser.h"
# include "expander/expander.h"
# include "converter/converter.h"
# include "pipex/pipex.h"

char	*wrap_readline(char *str);
char	*ft_getenviron(char *key);

#endif