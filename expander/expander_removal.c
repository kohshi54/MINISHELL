#include "expander.h"

/*
2.6.7 Quote Removal
The quote characters ( <backslash>, single-quote, and double-quote)
that were present in the original word shall be removed unless they have themselves been quoted.

In minishell, single-quote and double-quote should be handled.
*/

void execute_quote_removal(t_cmd_node *cur_cmd)
{
	char *tmp;

	while (cur_cmd)
	{
		ft_printf("before: %s\n", cur_cmd->str);
		if (cur_cmd->str)
		{
			tmp = cur_cmd->str;
			cur_cmd->str = removal(cur_cmd->str);
			free(tmp);
		}
		ft_printf("after: %s\n", cur_cmd->str);
		cur_cmd = cur_cmd->next;
	}
}

void remove_quote(t_node *cur)
{
	char *tmp;

	if (cur->left)
		remove_quote(cur->left);
	if (cur && cur->kind != ND_PIPE)
		execute_quote_removal(cur->cmd);
	else
	{
		ft_printf("before: %s\n", cur->str);
		tmp = cur->str;
		cur->str = removal(cur->str);
		free(tmp);
		ft_printf("after: %s\n", cur->str);
	}
	if (cur->right)
		remove_quote(cur->right);
}
