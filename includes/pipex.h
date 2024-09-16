/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:10:45 by phautena          #+#    #+#             */
/*   Updated: 2024/09/16 18:09:09 by phautena         ###   ########.fr       */
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
	int		**pipes;
	char	**splitted_path;
}	t_pipex;

////main.c////
int		create_pipes(t_pipex *pipex);
int		create_process(t_pipex *pipex, char *argv[], char *envp[]);
int		build_and_exec(t_pipex *pipex, char *binary, char *envp[], int iterator);
void	close_pipes_children(t_pipex *pipex, int iterator);
void	close_all_pipes(t_pipex *pipex);
////pipex_build.c////
char	**build_command(t_pipex *pipex, char *binary, char *envp[]);
char	*get_binary_path(t_pipex *pipex, char *binary);

////pipex_utils.c////
void	init_structure(t_pipex *pipex, int argc);
int		init_files(t_pipex *pipex, char *argv[], int argc);
void	ft_free(t_pipex *pipex);
void	ft_free_double_array(char	**array);
int		get_path(t_pipex *pipex, char *envp[]);

#endif
