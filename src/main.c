/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:22:11 by ainthana          #+#    #+#             */
/*   Updated: 2025/03/31 22:55:15 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	pid_t	pid1;

	if (ac == 5)
	{
		if (pipe(fd) == -1)
		{
			close(fd[0]);
			close(fd[1]);
			perror("pipe");
		}
		pid1 = fork();
		if (pid1 == 0)
			child(av, env, fd);
		waitpid(pid1, NULL, 0);
		parent(av, env, fd);
	}
	else
	{
		perror("bad arguments");
		exit(EXIT_FAILURE);
	}
	return (0);
}
