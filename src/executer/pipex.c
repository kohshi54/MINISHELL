#include "pipex.h"

void	execute_first(t_simplecmd *cur, int new_pipe[2], int here_read)
{
	extern char **environ;

	close(new_pipe[READ]);
	dup2(new_pipe[WRITE], STDOUT_FILENO);
	close(new_pipe[WRITE]);
	if (here_read != 0)
	{
		dup2(here_read, STDIN_FILENO);
		close(here_read);
	}
	execute_command(cur);
}

void	execute_last(t_simplecmd *cur, int old_read_end, int here_read)
{
	extern char **environ;

	dup2(old_read_end, STDIN_FILENO);
	close(old_read_end);
	if (here_read != 0)
	{
		dup2(here_read, STDIN_FILENO);
		close(here_read);
	}
	execute_command(cur);
}

void	execute_middle(t_simplecmd *cur, int new_pipe[2], int old_read_end, int here_read)
{
	extern char **environ;

	close(new_pipe[READ]);
	dup2(old_read_end, STDIN_FILENO);
	close(old_read_end);
	dup2(new_pipe[WRITE], STDOUT_FILENO);
	close(new_pipe[WRITE]);
	if (here_read != 0)
	{
		dup2(here_read, STDIN_FILENO);
		close(here_read);
	}
	execute_command(cur);
}

size_t get_node_count(t_simplecmd **cur)
{
	size_t i;

	i = 0;
	while (*cur)
	{
		// ft_printf("cmdname: %s, fname: %s, type: %d\n", (*cur)->cmd->str, (*cur)->redirect ? (*cur)->redirect->fname : NULL, (*cur)->redirect ? (*cur)->redirect->type : 0);
		cur++;
		i++;
	}
	return (i);
}

void execute_exit(t_simplecmd **cur)
{
	while (*cur && (*cur)->cmd)
	{
		// ft_printf("cur->str; %s\n", (*cur)->cmd->str);
		if (ft_strncmp((*cur)->cmd->str, "exit", 4) == 0)
			exit(0);
		cur++;
	}
}

void	handle_heredoc(t_simplecmd *cmd, int here_pipe[2])
{
	t_redirect	*cur_red;

	cur_red = cmd->redirect;
	while (cur_red)
	{
		if (cur_red->type == R_HEREDOC)
		{
			pipe(here_pipe);
			ft_heredoc(cmd->redirect->fname, here_pipe[WRITE]);
			close(here_pipe[WRITE]);
		}
		cur_red = cur_red->next;
	}
}

void	execute_one_simplecmd(t_simplecmd *cur)
{
	int			here_pipe[2];
	int			status;

	handle_heredoc(cur, here_pipe);
	if (fork() == 0)
	{
		if (here_pipe[READ] != 0)
		{
			dup2(here_pipe[READ], STDIN_FILENO);
			close(here_pipe[READ]);
		}
		execute_command(cur);
		exit(1);
		// system("leaks -q minishell");
	}
	close(here_pipe[READ]);
	wait(&status);
}

void	execute_multiple_simplecmd(t_simplecmd **cur, size_t cmdnum)
{
	int		new_pipe[2];
	size_t	i;
	int here_pipe[2];
	int old_read_end;

	i = 0;
	while (i < cmdnum)
	{
		if (i != cmdnum - 1)
			pipe(new_pipe);
		handle_heredoc(cur[i], here_pipe);
		if (fork() == 0)
		{
			if (i == 0)
				execute_first(cur[i], new_pipe, here_pipe[READ]);
			else if (i == cmdnum - 1)
				execute_last(cur[i], old_read_end, here_pipe[READ]);
			else
				execute_middle(cur[i], new_pipe, old_read_end, here_pipe[READ]);
		}
		if (i != 0)
			close(old_read_end);
		old_read_end = new_pipe[READ];
		close(new_pipe[WRITE]);
		if (here_pipe[READ] != 0)
			close(here_pipe[READ]);
		// waitpid(pid, &status, 0);
		i++;
	}
}

int pipex(t_simplecmd **cur)
{
	int status;
	size_t cmdnum;

	execute_exit(cur);
	cmdnum = get_node_count(cur);
	// ft_printf("cmdnum: %d\n", cmdnum);
	if (cmdnum < 2)
	{
		execute_one_simplecmd(cur[0]);
		return (0);
	}
	execute_multiple_simplecmd(cur, cmdnum);
	while (cmdnum-- > 0)
	{
		wait(&status);
		// waitpid(pid, &status, 0);
	}
	return (0);
}