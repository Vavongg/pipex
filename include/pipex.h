/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:34:11 by ainthana          #+#    #+#             */
/*   Updated: 2025/04/01 11:53:23 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../ft_printf/ft_printf.h"

//src
char	**ft_split(char *str, char sep);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strjoin(char *s1, char *s2);
void	free_args(char **args);
void	child(char **av, char **envp, int fd[2]);
void	parent(char **av, char **envp, int fd[2]);
char	*find_path(char *cmd, char **envp);
void	exec_cmd(char *argv, char **envp);
char	**get_paths_from_env(char **envp);
char	*get_path(char *cmd, char **envp);
char	*find_executable(char *cmd, char **paths);

#endif 
