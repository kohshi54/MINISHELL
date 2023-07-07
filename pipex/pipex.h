/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyamaguc <kyamaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 21:04:14 by kyamaguc          #+#    #+#             */
/*   Updated: 2023/07/07 21:06:23 by kyamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include "../converter/converter.h"
# include "../minishell.h"
# include <fcntl.h>

typedef struct s_varlist
{
	t_list	*envvars;
	t_list	*vars;
}	t_varlist;

# define READ 0
# define WRITE 1

/* pipex.c */
int		pipex(t_simplecmd **cmds);

/* pipex_utils.c */
char	*get_path_from_env(void);
char	*get_command_path(char *command);
void	execute_command(t_simplecmd *cmd);

/* heredoc.c */
int		ft_heredoc(char *limiter, int writefd);

#endif