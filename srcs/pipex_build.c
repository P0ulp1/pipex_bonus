/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_build.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:27:56 by phautena          #+#    #+#             */
/*   Updated: 2024/09/23 14:32:25 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**build_command(t_pipex *pipex, char *binary, char *envp[])
{
	char	**command;
	char	*temp;

	if (pipex->splitted_path == NULL)
		if (get_path(pipex, envp) != 0)
			return (perror("Path"), NULL);
	command = ft_split(binary, ' ');
	if (command == NULL)
		return (NULL);
	if (command[0][0] == '/')
	{
		if (access(command[0], X_OK) == 0)
			return (command);
		else
			return (perror("Command not found"), NULL);
	}
	temp = ft_strjoin("/", command[0]);
	if (temp == NULL)
		return (NULL);
	free(command[0]);
	command[0] = get_binary_path(pipex, temp);
	if (command[0] == NULL)
		return (ft_free_double_array(command), NULL);
	return (command);
}

char	*get_binary_path(t_pipex *pipex, char *binary)
{
	int		i;
	char	*temp;

	i = 0;
	while (pipex->splitted_path[i] != NULL)
	{
		temp = ft_strjoin(pipex->splitted_path[i], binary);
		if (temp == NULL)
			return (free(binary), NULL);
		if (access(temp, X_OK) == 0)
			return (free(binary), temp);
		free(temp);
		i++;
	}
	perror("Command not found");
	free(binary);
	return (NULL);
}

int	exec_all(t_pipex *pipex, char *argv[])
{
	int		i;
	char	**command;

	i = 0;
	dup2(pipex->infile, STDIN_FILENO);
	while (i < pipex->process_n - 1)
	{
		if (exec_children(pipex, argv[i + 2]) != 0)
			break ;
		i++;
	}
	dup2(pipex->outfile, STDOUT_FILENO);
	close(pipex->infile);
	close(pipex->outfile);
	command = build_command(pipex, argv[pipex->process_n + 1], pipex->envp);
	if (command == NULL)
		return (2);
	if (execve(command[0], command, pipex->envp) == -1)
		return (perror("Executing Command"), 3);
	free(command);
	return (0);
}

int	exec_children(t_pipex *pipex, char *binary)
{
	int		pipefd[2];
	pid_t	pid;
	char	**command;

	command = build_command(pipex, binary, pipex->envp);
	if (command == NULL)
		return (1);
	if (pipe(pipefd) == -1)
		return (perror("Pipe"), 2);
	pid = fork();
	if (pid == -1)
		return (perror("Fork"), 3);
	if (exec_children_bis(pipex, pid, pipefd, command) != 0)
		return (4);
	free(command);
	return (0);
}

int	exec_children_bis(t_pipex *pipex, pid_t pid, int pipefd[2], char **command)
{
	if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		close(pipex->infile);
		close(pipex->outfile);
		if (execve(command[0], command, pipex->envp) == -1)
			return (perror("Command execution"), 1);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		wait(NULL);
	}
	return (0);
}
