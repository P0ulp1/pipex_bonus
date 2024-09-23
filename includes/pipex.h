/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:10:45 by phautena          #+#    #+#             */
/*   Updated: 2024/09/23 14:33:31 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../ft_printf/includes/ft_printf.h"
# include "../Libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_pipex
{
	int		process_n;
	int		infile;
	int		outfile;
	char	**splitted_path;
	char	**envp;
}	t_pipex;

////main.c////

////pipex_build.c////
char	**build_command(t_pipex *pipex, char *binary, char *envp[]);
char	*get_binary_path(t_pipex *pipex, char *binary);
int		exec_children(t_pipex *pipex, char *binary);
int		exec_all(t_pipex *pipex, char *argv[]);
int		exec_children_bis(t_pipex *pipex, pid_t pid, int pipefd[2], char **command);
////pipex_utils.c////
void	init_structure(t_pipex *pipex, int argc, char *envp[]);
int		init_files(t_pipex *pipex, char *argv[], int argc);
void	ft_free(t_pipex *pipex);
void	ft_free_double_array(char	**array);
int		get_path(t_pipex *pipex, char *envp[]);

#endif
