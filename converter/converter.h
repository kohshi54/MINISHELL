#ifndef CONVERTER_H
# define CONVERTER_H

# include "../minishell.h"

/* converter.c */
char **converter(t_node *cur);

/* converter_utils.c */
char	*ft_strconnect(char *s1, char *s2, char *s3);
int		get_list_size(t_cmd_node *lst);
bool	heredoc_exist(t_cmd_node *cmd);
void	count_node(t_node *cur, size_t *count);
size_t	get_node_count(t_node *cur);

#endif