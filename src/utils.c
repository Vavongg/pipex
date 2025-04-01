/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:24:59 by ainthana          #+#    #+#             */
/*   Updated: 2025/04/01 13:11:14 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child(char **av, char **env, int fd[2])
{
	int		filein;

	filein = open(av[1], O_RDONLY, 0777);
	if (filein == -1)
	{
		perror(av[1]);
		close(fd[0]);
		close(fd[1]);
		close(filein);
		exit(EXIT_FAILURE);
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(filein);
	exec_cmd(av[2], env);
}

void	parent(char **av, char **env, int fd[2])
{
	int		fileout;

	fileout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
	{
		perror(av[4]);
		close(fd[1]);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
	close(fileout);
	exec_cmd(av[3], env);
}

char	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(env[i], "PATH=", 5) == 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	free_args(paths);
	return (NULL);
}

void	exec_cmd(char *argv, char **env)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (!cmd)
		return ;
	if (access(cmd[0], F_OK) == 0)
		path = cmd[0];
	else
		path = find_path(cmd[0], env);
	if (!path)
	{
		free_args(cmd);
		perror("command not found");
		exit(127);
	}
	if (execve(path, cmd, env) == -1)
	{
		free(path);
		exit(126);
	}
}
