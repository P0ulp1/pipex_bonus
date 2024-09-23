/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:14:11 by phautena          #+#    #+#             */
/*   Updated: 2024/09/23 13:21:07 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_structure(t_pipex *pipex, int argc)
{
	pipex->process_n = argc - 3;
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->splitted_path = NULL;
}

int	init_files(t_pipex *pipex, char *argv[], int argc)
{
	if (access(argv[1], R_OK) == -1)
	{
		perror(argv[1]);
		return (1);
	}
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
	{
		perror(argv[1]);
		return (2);
	}
	pipex->outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (pipex->outfile == -1)
	{
		perror(argv[argc - 1]);
		return (3);
	}
	if (access(argv[argc - 1], W_OK) == -1)
	{
		perror(argv[argc - 1]);
		return (4);
	}
	return (0);
}

void	ft_free(t_pipex *pipex)
{
	if (pipex->splitted_path != NULL)
		ft_free_double_array(pipex->splitted_path);
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
}

void	ft_free_double_array(char	**array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

int	get_path(t_pipex *pipex, char *envp[])
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			if (path == NULL)
				return (1);
			break ;
		}
		i++;
	}
	pipex->splitted_path = ft_split(path, ':');
	free(path);
	if (pipex->splitted_path == NULL)
		return (2);
	return (0);
}
