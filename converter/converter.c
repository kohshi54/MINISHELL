#include "converter.h"

/*
Convert AST into list of dobuble arryay.
During the process make new command when heredoc is found.
if heredoc detected, configure node following the rule below:
before: echo hoge << eof fuga
after: cat << eof | echo hoge fuga
*/

void make_double_array(t_node *cur, char **cmds, size_t *i)
{
	t_cmd_node *tmp;
	char *line;
	char *tmp_line;

	if (cur->left)
		make_double_array(cur->left, cmds, i);
	if (cur->kind != ND_PIPE)
	{
		tmp = cur->cmd;
		line = "";
		if (heredoc_exist(tmp) == true)
		{
			cmds[*i] = ft_strdup("cat << eof");
			(*i)++;
		}
		while (tmp)
		{
			if (tmp->kind == ND_REDIRECTION && ft_strncmp(tmp->str, "<<", 2) == 0)
			{
				free(tmp->str);
				free(tmp->next->str);
				tmp = tmp->next->next;
				continue;
			}
			tmp_line = line;
			line = ft_strconnect(line, " ", tmp->str);
			if (ft_strncmp(tmp_line, "", 1) != 0)
				free(tmp_line);
			free(tmp->str);
			tmp = tmp->next;
		}
		cmds[*i] = line;
		(*i)++;
	}
	if (cur->right)
		make_double_array(cur->right, cmds, i);
}

char **converter(t_node *cur)
{
	size_t count;
	char **cmds;
	size_t i;

	count = get_node_count(cur);
	cmds = malloc(sizeof(char *) * (count + 1));
	i = 0;
	make_double_array(cur, cmds, &i);
	cmds[i] = NULL;
	// print_converted(cmds);
	return (cmds);
}

/*
void print_converted(char **cur)
{
	size_t i;

	i = 0;
	while (cur[i])
	{
		ft_printf("cmd: %s\n", cur[i]);
		i++;
	}
}
*/