#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include "../libft/ft_printf.h"

typedef struct s_varlist
{
	t_list *envvars;
	t_list *vars;
} t_varlist;

/* pipex.c */
int pipex(char *argv[], t_varlist *varlist);
// int pipex(char *argv[]);
#define READ 0
#define WRITE 1

char *get_path_from_env();
char *get_command_path(char *command);
void execute_command(char *cmdline, t_varlist *varlist);
// void execute_command(char *cmdline);

#endif