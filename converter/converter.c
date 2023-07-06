#include "converter.h"

/*
Convert AST into list of dobuble arryay of t_simplecmd.
During the process make new command when heredoc is found.
if heredoc detected, configure node following the rule below:
before: echo hoge << eof fuga
after: cat << eof | echo hoge fuga
*/

int get_redirect_type(char *cmd)
{
	if (ft_strncmp(cmd, "<", 1) == 0)
		return (R_INPUT);
	if (ft_strncmp(cmd, ">", 1) == 0)
		return (R_OUTPUT);
	if (ft_strncmp(cmd, ">>", 2) == 0)
		return (R_APND_OUTPUT);
	if (ft_strncmp(cmd, "<<", 2) == 0)
		return (R_HEREDOC);
	return (0);
}

t_redirect *add_redirect(t_cmd_node *cur, t_redirect *prev, t_simplecmd *cmd)
{
	t_redirect *new;

	new = malloc(sizeof(t_redirect));
	new->fname = cur->next->str;
	new->type = get_redirect_type(cur->str);
	new->next = NULL;
	if (prev)
		prev->next = new;
	else
		cmd->redirect = new;
	return (new);
}

t_cmd	*add_cmd(t_cmd_node *cur, t_cmd *prev, t_simplecmd *cmd)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	new->str = cur->str;
	new->next = NULL;
	if (prev)
		prev->next = new;
	else
		cmd->cmd = new;
	return (new);
}

t_simplecmd	*init_simplecmd(void)
{
	t_simplecmd	*new;

	new = malloc(sizeof(t_simplecmd));
	new->cmd = NULL;
	new->redirect = NULL;
	return (new);
}

void make_double_array(t_node *cur, t_simplecmd **cmds, size_t *i)
{
	t_cmd_node	*tmp;
	t_redirect	*red_cur;
	t_cmd		*cmd_cur;

	if (cur->left)
		make_double_array(cur->left, cmds, i);
	if (cur->kind != ND_PIPE)
	{
		cmds[*i] = init_simplecmd();
		tmp = cur->cmd;
		red_cur = NULL;
		cmd_cur = NULL;
		while (tmp)
		{
			if (tmp->kind == ND_REDIRECTION)
			{
				red_cur = add_redirect(tmp, red_cur, cmds[*i]);
				tmp = tmp->next->next;
			}
			else
			{
				cmd_cur = add_cmd(tmp, cmd_cur, cmds[*i]);
				tmp = tmp->next;
			}
		}
		(*i)++;
	}
	if (cur->right)
		make_double_array(cur->right, cmds, i);
}

void print_converted(t_simplecmd **cur)
{
	size_t	i;

	i = 0;
	while (cur[i])
	{
		while (cur[i]->cmd)
		{
			ft_printf("cmd: %s\n", cur[i]->cmd->str);
			cur[i]->cmd = cur[i]->cmd->next;
		}
		while (cur[i]->redirect)
		{
			ft_printf("redirect: %s\n", cur[i]->redirect->fname);
			cur[i]->redirect = cur[i]->redirect->next;
		}
		printf("==\n");
		i++;
	}
}

t_simplecmd **converter(t_node *cur)
{
	size_t		count;
	t_simplecmd **cmds;
	size_t		i;

	count = get_node_count2(cur);
	cmds = malloc(sizeof(t_simplecmd *) * (count + 1));
	i = 0;
	make_double_array(cur, cmds, &i);
	cmds[i] = NULL;
	// print_converted(cmds);
	return (cmds);
}
