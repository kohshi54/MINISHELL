#include "pipex.h"

char *get_path_from_env()
{
	extern char **environ;

	while (*environ)
	{
		if (ft_strncmp(*environ, "PATH=", 5) == 0)
		{
			ft_strtrim_gc(*environ, "PATH=", &ptr_list);
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
	path_array = ft_split_gc(path, ':', &ptr_list);
	command = ft_strjoin_gc("/", command, &ptr_list);
	while (*path_array)
	{
		command_path = ft_strjoin_gc(*path_array, command, &ptr_list);
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
	cmd = ft_malloc(sizeof(char *) * (num + 1), &ptr_list);
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
	t_redirect	*cur_red;

	cur_red = cur->redirect;
	while (cur_red)
	{
		if (cur_red->type == R_INPUT)
		{
			fd = open(cur_red->fname, O_RDONLY);
			if (fd == -1)
			{
				ft_printf("no such file or directory\n");
				return ;
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		if (cur_red->type == R_OUTPUT)
		{
			fd = open(cur_red->fname, (O_RDWR | O_CREAT | O_TRUNC), 0664);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		if (cur_red->type == R_APND_OUTPUT)
		{
			fd = open(cur_red->fname, (O_RDWR | O_APPEND | O_CREAT), 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		cur_red = cur_red->next;
	}
	cmd = make_cmd_array(cur);
	path = get_command_path(cmd[0]);
	if (execve(path, cmd, environ) == -1)
	{
		write(STDERR_FILENO, "command not found\n", 18);
		exit(122);
	}
}