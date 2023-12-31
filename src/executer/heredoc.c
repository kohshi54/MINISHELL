/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohshi54 <kohshi54@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 07:55:25 by tyonezaw          #+#    #+#             */
/*   Updated: 2023/11/13 07:14:08 by kohshi54         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Originally composed by my dear teammate tyonezaw. */

#include "minishell.h"
#include "pipex.h"

static void write_list(t_list *list, int writefd)
{
	t_list *tmplist;
	char *str;

	while (list)
	{
		str = list->content;
		write(writefd, str, ft_strlen(str));
		write(writefd, "\n", 1);
		tmplist = list;
		list = list->next;
		ft_lstdelone(tmplist, free);
	}
}

int ft_heredoc(char *limiter, int writefd)
{
	t_list *list;
	char *line;

	list = NULL;
	if (!limiter)
		exit(1);
	while (1)
	{
		line = wrap_readline("> ");
		if (!line)
			exit(0);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		if (!list)
			list = ft_lstnew(line);
		else
			ft_lstadd_back(&list, ft_lstnew(line));
	}
	write_list(list, writefd);
	return (1);
}