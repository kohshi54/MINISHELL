#include "minishell.h"

void print_token_list(t_token *token)
{
	while (token && token->kind != TK_EOF)
	{
		printf("token: %s, kind: %d\n", token->str, token->kind);
		token = token->next;
	}
	if (token)
		printf("token: %s, kind: %d\n", token->str, token->kind);
}

int main(void)
{
	char *line;
	t_token *token_list;

	line = wrap_readline(NULL);
	// printf("%s\n", line);
	token_list = tokenize(line);
	// if (token_list == NULL)
		// return (0);
	print_token_list(token_list);
	return (0);
}