/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:47:43 by ainthana          #+#    #+#             */
/*   Updated: 2025/04/02 10:50:30 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
