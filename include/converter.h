/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohshi54 <kohshi54@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 19:13:52 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/11/13 07:01:14 by kohshi54         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERTER_H
# define CONVERTER_H

# include "minishell.h"
# include "libft.h"
# include "parser.h"

typedef enum e_redirect_type
{
	R_INPUT,
	R_OUTPUT,
	R_APND_OUTPUT,
	R_HEREDOC,
}	t_redirect_type;

typedef struct s_redirect
{
	char				*fname;
	t_redirect_type		type;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_cmd
{
	char			*str;
	struct s_cmd	*next;
}	t_cmd;

/* converter.c */
t_simplecmd	**converter(t_node *cur);

/* converter_utils.c */
char		*ft_strconnect(char *s1, char *s2, char *s3);
int			get_list_size(t_cmd_node *lst);
bool		heredoc_exist(t_cmd_node *cmd);
void		count_node2(t_node *cur, size_t *count);
size_t		get_node_count2(t_node *cur);

#endif