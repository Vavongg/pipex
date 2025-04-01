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

char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*good_path;

	if (!cmd)
		return (NULL);
	paths = get_paths_from_env(envp);
	good_path = find_executable(cmd, paths);
	return (good_path);

}
char	**get_paths_from_env(char **envp)
{
	int	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

char	*find_executable(char *cmd, char **paths)
{
	int		i;
	char	*full_path;
	char	*tmp_path;

	if (!paths)
		return (cmd);
	i = 0;
	while (paths[i])
	{
		tmp_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	free_args(paths);
	return (cmd);
}

void	exec_cmd(char *argv, char **env)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (!cmd)
		return ;
	path = get_path(cmd[0], env);
	if (!path)
	{
		free_args(cmd);
		perror("command not found");
		exit(127);
	}
	if (execve(path, cmd, env) == -1)
	{
		free(path);
		perror("command not found");
		exit(126);
	}
}
