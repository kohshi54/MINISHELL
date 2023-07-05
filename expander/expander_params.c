#include "expander.h"

/*
The '$' character is used to introduce parameter expansion, command substitution, or arithmetic evaluation.
If an unquoted '$' is followed by a character that is not one of the following:
・A numeric character
・The name of one of the special parameters (see Special Parameters)
・A valid first character of a variable name
・A <left-curly-bracket> ( '{' )
・A <left-parenthesis>

In minishell, only numeric character is considered.
*/

char *make_word(t_word *cur)
{
	char *line;

	line = NULL;
	while (cur)
	{
		ft_printf("str: %s\n", cur->str);
		if (cur->in_single_quote == false && cur->str[0] == '$')
			cur->str = ft_getenviron(&(cur->str[1]));
		ft_printf("exp: %s\n", cur->str);
		if (cur->str)
			line = ft_strjoin_null_accept(line, cur->str);
		cur = cur->next;
	}
	// printf("expanded line: %s\n", line);
	return (line);
}

bool is_env_assignable(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}

void update_quote_flg(int *quote_flg, char c)
{
	if (*quote_flg == NONE && c == SINGLE_QUOTE)
		*quote_flg = SINGLE;
	else if (*quote_flg == NONE && c == DOUBLE_QUOTE)
		*quote_flg = DOUBLE;
	else if (*quote_flg == SINGLE && c == SINGLE_QUOTE)
		*quote_flg = NONE;
	else if (*quote_flg == DOUBLE && c == DOUBLE_QUOTE)
		*quote_flg = NONE;
}

void scan_param(char **line, int *quote_flg)
{
	(*line)++;
	while (is_env_assignable(**line) == true)
	{
		update_quote_flg(quote_flg, **line);
		(*line)++;
	}
}

void scan_line(char **line, int *quote_flg)
{
	while (**line && **line != '$')
	{
		update_quote_flg(quote_flg, **line);
		(*line)++;
	}
}

char *find_params_and_replace(char *line)
{
	t_word head;
	char *start;
	t_word *cur;
	int quote_flg;

	cur = &head;
	quote_flg = NONE;
	while (*line)
	{
		start = line;
		if (*line && *line == '$')
			scan_param(&line, &quote_flg);
		else
			scan_line(&line, &quote_flg);
		cur = append_new(cur, start, line - start, quote_flg);
	}
	return (make_word(head.next));
}

void execute_parameter_expansion(t_cmd_node *cur_cmd)
{
	char *tmp;

	while (cur_cmd)
	{
		if (cur_cmd->kind == ND_REDIRECTION && ft_strncmp(cur_cmd->str, "<<", 2) == 0)
		{
			if (cur_cmd->next)
			{
				cur_cmd = cur_cmd->next->next;
				continue;
			}
		}
		tmp = cur_cmd->str;
		cur_cmd->str = find_params_and_replace(cur_cmd->str);
		free(tmp);
		cur_cmd = cur_cmd->next;
	}
}

void expand_params(t_node *cur)
{
	if (cur->left)
		expand_params(cur->left);
	if (cur->kind != ND_PIPE)
		execute_parameter_expansion(cur->cmd);
	if (cur->right)
		expand_params(cur->right);
}
