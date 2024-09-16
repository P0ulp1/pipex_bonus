/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_build.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:27:56 by phautena          #+#    #+#             */
/*   Updated: 2024/09/16 15:27:45 by phautena         ###   ########.fr       */
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
	perror("command not found");
	free(binary);
	return (NULL);
}
