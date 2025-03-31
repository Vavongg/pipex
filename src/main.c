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
	(void)env;
	int fd[2];
	pid_t	pid1;
	
	if (ac != 5)
		exit(EXIT_FAILURE);
	pid1 = fork();
	if (pipe(fd) == -1)
	{
		perror("fd");
		return (1);
	}
	if (pid1 == 0)
		create_fork1(av, env, fd);
	create_fork2(av, env, fd);
	close(fd[0]);
	close(fd[1]);
	return (0);
}
