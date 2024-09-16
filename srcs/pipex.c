/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:11:46 by phautena          #+#    #+#             */
/*   Updated: 2024/09/16 18:26:54 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc < 5)
		return (ft_printf("Not enough arguments\n"), 1);
	init_structure(&pipex, argc);
	if (init_files(&pipex, argv, argc) != 0)
		return (ft_free(&pipex), 2);
	if (create_pipes(&pipex) != 0)
		return (ft_free(&pipex), 3);
	if (create_process(&pipex, argv, envp) != 0)
		return (ft_free(&pipex), 4);
	ft_free(&pipex);
	return (0);
}

int	create_pipes(t_pipex *pipex)
{
	int	pipes[pipex->process_n + 1][2];
	int	i;

	i = 0;
	while (i < pipex->process_n + 1)
	{
		if (pipe(pipes[i]) == -1)
			return (perror("Pipes"), 1);
		i++;
	}
	pipex->pipes = pipes;
	return (0);
}

int	create_process(t_pipex *pipex, char *argv[], char *envp[])
{
	int	i;
	int	pids[pipex->process_n];

	i = 0;
	while (i < pipex->process_n)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (perror("Forking"), 1);
		if (pids[i] == 0)
		{
			if (build_and_exec(pipex, argv[i + 2], envp, i) != 0)
				return (ft_free(pipex), 2);
			return (0);
		}
		wait(NULL);
		i++;
	}
	return (0);
}

int	build_and_exec(t_pipex *pipex, char *binary, char *envp[], int iterator)
{
	char	**command;

	command = build_command(pipex, binary, envp);
	if (command == NULL)
		return (1);
	// if (iterator == 0)
	// {
	// 	dup2(pipex->infile, STDIN_FILENO);
	// 	dup2(pipex->pipes[iterator][1], STDOUT_FILENO);
	// }
	// else if (iterator == pipex->process_n)
	// {
	// 	dup2(pipex->pipes[iterator][0], STDIN_FILENO);
	// 	dup2(pipex->outfile, STDOUT_FILENO);
	// }
	// else
	// {
	// 	dup2(pipex->pipes[iterator][0], STDIN_FILENO);
	// 	dup2(pipex->pipes[iterator + 1][1], STDOUT_FILENO);
	// }
	// close_pipes_children(pipex, iterator);
	// if (execve(command[0], command, envp) == -1)
	// 	return (perror("Command execution"), 2);
	// close(pipex->pipes[iterator][0]);
	// close(pipex->pipes[iterator + 1][1]);
	// free(command);
	// command = NULL;
	if (iterator == 0)
	{
		dup2(pipex->infile, STDIN_FILENO);
		dup2(pipex->pipes[1][1], STDOUT_FILENO);
	}
	else if (iterator == 1)
	{
		dup2(pipex->pipes[1][0], STDIN_FILENO);
		dup2(pipex->outfile, STDOUT_FILENO);
	}
	execve(command[0], command, envp);
	(void)iterator;
	return (0);
}

void	close_pipes_children(t_pipex *pipex, int iterator)
{
	int	j;

	j = 0;
	while (j < pipex->process_n + 1)
	{
		if (iterator != j)
			close(pipex->pipes[j][0]);
		if (iterator + 1 != j)
			close(pipex->pipes[j][1]);
		j++;
	}
}
