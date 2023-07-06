#include "pipex.h"

char *get_path_from_env()
{
	extern char **environ;

	while (*environ)
	{
		if (ft_strncmp(*environ, "PATH=", 5) == 0)
		{
			ft_strtrim(*environ, "PATH=");
			return (*environ);
		}
		environ++;
	}
	return ("not found");
}

char *get_command_path(char *command)
{
	char *path;
	char **path_array;
	char *command_path;
	extern char **environ;

	path = get_path_from_env();
	path_array = ft_split(path, ':');
	command = ft_strjoin("/", command);
	while (*path_array)
	{
		command_path = ft_strjoin(*path_array, command);
		if (access(command_path, X_OK) == 0)
		{
			return (command_path);
		}
		path_array++;
	}
	return ("not found");
}

size_t count_node(t_simplecmd *cur)
{
	size_t	i;
	t_cmd	*tmp;

	i = 0;
	tmp = cur->cmd;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char **make_cmd_array(t_simplecmd *cur)
{
	char	**cmd;
	size_t	num;
	char	**head;

	num = count_node(cur);
	cmd = malloc(sizeof(char *) * (num + 1));
	head = cmd;
	while (cur->cmd)
	{
		*cmd = cur->cmd->str;
		cur->cmd = cur->cmd->next;
		cmd++;
	}
	*cmd = NULL;
	return (head);
}

void execute_command(t_simplecmd *cur)
{
	char **cmd;
	char *path;
	extern char **environ;
	int	fd;

	if (cur->redirect)
	{
		if (cur->redirect->type == R_INPUT)
		{
			fd = open(cur->redirect->fname, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
	}
	cmd = make_cmd_array(cur);
	path = get_command_path(cmd[0]);
	execve(path, cmd, environ);
}