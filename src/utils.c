/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:24:59 by ainthana          #+#    #+#             */
/*   Updated: 2025/03/28 17:39:17 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	create_fork1(int ac, char **av, char **env, int fd[2])
{
	(void)ac;
	(void)env;
	pid_t	pid1;

	pid1 = fork();
	if (pid1 < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
	{
		int infile = open(av[1], O_RDONLY);
		if (infile < 0)
		{
			perror(av[1]);
			exit(EXIT_FAILURE);
		}

		dup2(infile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(infile);
		close(fd[0]);
		close(fd[1]);
		exit(EXIT_FAILURE);
	}
}

void	create_fork2(int ac, char **av, char **env, int fd[2])
{
	(void)ac;
	(void)env;
	pid_t	pid2;

	pid2 = fork();
	if (pid2 < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0)
	{
		int fd_out = open(av[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1)
		{
			perror(av[4]);
			exit(EXIT_FAILURE);
		}

		dup2(fd[0], STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		close(fd[0]);
		close(fd[1]);
		exit(EXIT_FAILURE);
	}
}
