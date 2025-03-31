/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:34:11 by ainthana          #+#    #+#             */
/*   Updated: 2025/03/31 22:53:26 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>      // open  
# include <unistd.h>     // close, read, write, access, dup, dup2, execve, fork, pipe, unlink  
# include <stdlib.h>     // malloc, free, exit  
# include <stdio.h>      // perror  
# include <string.h>     // strerror  
# include <sys/types.h>  // wait, waitpid  
# include <sys/wait.h>   // wait, waitpid
# include "../ft_printf/ft_printf.h"

//src
void	parse_args(int ac, char **av, char **env);
int		is_valid_command(char *cmd, char **env);
char	**ft_split(char *str, char sep);
int		ft_strlen(char *str);
char	*ft_strdup(char *str);
void	free_args(char **args);
void	create_fork1(char **av, char **env, int fd[2]);
void	create_fork2(char **av, char **env, int fd[2]);

#endif 
