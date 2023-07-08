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

void print_tree(t_node *cur)
{
	t_cmd_node *tmp;

	if (cur && cur->left)
		print_tree(cur->left);
	if (cur && cur->kind != ND_PIPE)
	{
		tmp = cur->cmd;
		while (tmp)
		{
			printf("%s ", tmp->str);
			tmp = tmp->next;
		}
	}
	else
	{
		printf("%s", cur->str);
	}
	printf("\n");
	if (cur && cur->right)
		print_tree(cur->right);
}

int main(void)
{
	char		*line;
	t_token		*token_list;
	t_node		*root;
	t_simplecmd	**cmds;
	// t_varlist	varlist;

	ptr_list = NULL;
	line = wrap_readline(NULL);
	// printf("%s\n", line);
	token_list = tokenize(line);
	if (token_list == NULL)
		return (0);
	print_token_list(token_list);
	root = parse(token_list);
	if (root == NULL)
		return (0);
	print_tree(root);
	root = expand(root);
	cmds = converter(root);
	// pipex(cmds, &varlist);
	pipex(cmds);
	free_all_mallocated_area(ptr_list);
	system("leaks -q minishell");
	return (0);
}