/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:11:46 by phautena          #+#    #+#             */
/*   Updated: 2024/09/23 14:32:35 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc < 5)
		return (ft_printf("Not enough arguments\n"), 1);
	init_structure(&pipex, argc, envp);
	if (init_files(&pipex, argv, argc) != 0)
		return (ft_free(&pipex), 2);
	if (exec_all(&pipex, argv) != 0)
		return (ft_free(&pipex), 3);
	ft_free(&pipex);
	return (0);
}


// HANDLE ABSENCE OF ENVP
