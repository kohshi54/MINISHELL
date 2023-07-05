#include "pipex.h"

void execute_first(char *cmd, int new_pipe[2], t_varlist *varlist)
{
	//	extern char **environ;

	close(new_pipe[READ]);
	dup2(new_pipe[WRITE], STDOUT_FILENO);
	close(new_pipe[WRITE]);
	execute_command(cmd, varlist);
}

void execute_last(char *cmd, int old_read_end, t_varlist *varlist)
{
	//	extern char **environ;

	dup2(old_read_end, STDIN_FILENO);
	close(old_read_end);
	execute_command(cmd, varlist);
}

void execute_middle(char *cmd, int new_pipe[2], int old_read_end, t_varlist *varlist)
{
	//	extern char **environ;

	close(new_pipe[READ]);
	dup2(old_read_end, STDIN_FILENO);
	close(old_read_end);
	dup2(new_pipe[WRITE], STDOUT_FILENO);
	close(new_pipe[WRITE]);
	execute_command(cmd, varlist);
}

void validate_input(int argc)
{
	if (argc < 3)
	{
		ft_printf("too few arguments\n");
		exit(0);
	}
}

size_t count_argv(char **argv)
{
	size_t i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void print_argv(char *argv[])
{
	while (*argv)
	{
		ft_printf("argv: %s\n", (*argv));
		argv++;
	}
}

void execute_exit(char *argv[])
{
	while (*argv)
	{
		if (ft_strncmp(*argv, "exit", 4) == 0)
			exit(0);
		argv++;
	}
}

// int pipex(int argc, char *argv[])
int pipex(char *argv[], t_varlist *varlist)
{
	int new_pipe[2];
	pid_t pid;
	//	extern char **environ;
	int status;
	size_t cmdnum;
	int old_read_end;
	size_t i;

	// validate_input(argc);
	print_argv(argv);
	execute_exit(argv);
	cmdnum = count_argv(argv);
	if (cmdnum < 2)
	{
		pid = fork();
		if (pid == 0)
			execute_command(argv[0], varlist);
		wait(&status);
		return (0);
	}
	i = 0;
	while (i < cmdnum)
	{
		if (i != cmdnum - 1)
			pipe(new_pipe);
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
				execute_first(argv[i], new_pipe, varlist);
			else if (i == cmdnum - 1)
				execute_last(argv[i], old_read_end, varlist);
			else
				execute_middle(argv[i], new_pipe, old_read_end, varlist);
		}
		if (i != 0)
			close(old_read_end);
		old_read_end = new_pipe[READ];
		close(new_pipe[WRITE]);
		// waitpid(pid, &status, 0);
		i++;
	}
	while (cmdnum-- > 0)
	{
		wait(&status);
		// waitpid(pid, &status, 0);
	}
	// ft_printf("success\n");
	return (0);
}
