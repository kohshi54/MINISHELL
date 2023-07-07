#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include "../converter/converter.h"
# include "../minishell.h"
# include <fcntl.h>

typedef struct s_varlist
{
	t_list *envvars;
	t_list *vars;
} t_varlist;

/* pipex.c */
// int pipex(char *argv[], t_varlist *varlist);
int pipex(t_simplecmd **cmds);
// int pipex(char *argv[]);
#define READ 0
#define WRITE 1

char *get_path_from_env();
char *get_command_path(char *command);
// void execute_command(char *cmdline, t_varlist *varlist);
void execute_command(t_simplecmd *cmd);
int ft_heredoc(char *limiter, int writefd);

#endif