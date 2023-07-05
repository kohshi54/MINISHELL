/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:21:45 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/07/05 21:24:48 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

/*
After parameter expansion, command substitution, and arithmetic expansion,
the shell shall scan the 
results of expansions and substitutions
that did not occur in double-quotes for 
field splitting and multiple fields can result.

The shell shall treat each character of the IFS as a delimiter
and use the delimiters as field terminators to split the results
of parameter expansion, command substitution, 
and arithmetic expansion into fields.

If the value of IFS is a <space>, <tab>, and <newline>, or
if it is unset, any sequence of <space>, <tab>, 
or <newline> characters at the beginning or end of the input shall be ignored
and any sequence of those characters within the input shall delimit a field.
For example, the input:

<newline><space><tab>foo<tab><tab>bar<space>

yields two fields, foo and bar.

If the value of IFS is null, no field splitting shall be performed.
Otherwise, the following rules shall be applied in sequence.
The term " IFS white space" is used to men any sequence 
(zero or more instances) of white-space charactersthat are in the IFS value
(for example, if IFS contains <space>/ <comma>/ <tab>, any sequence 
of <space> and <tab> characters is considered IFS white space).

IFS white space shall be ignored at the beginning and end of the input.
Each occurrence in the input of an IFS character that is not IFS white space,
along with any adjacent IFS white space, shall delimit a field, 
as described previously.

Non-zero-length IFS white space shall delimit a field.

In minishell,???
*/

void	execute_field_splitting(t_cmd_node *cur_cmd, char *ifs)
{
	while (cur_cmd)
	{
		split_node_when_presence_of_ifs(cur_cmd, ifs);
		cur_cmd = cur_cmd->next;
	}
}

void	split_field(t_node *cur)
{
	char	*ifs;

	ifs = " @"; //replace with get_ifs() later.
	if (cur->left)
		split_field(cur->left);
	if (cur->kind != ND_PIPE)
		execute_field_splitting(cur->cmd, ifs);
	if (cur->right)
		split_field(cur->right);
}
