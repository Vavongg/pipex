/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:22:11 by ainthana          #+#    #+#             */
/*   Updated: 2025/03/28 18:09:12 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av, char **env)
{
	(void)env;
	int fd[2];

	if (pipe(fd) == -1)
	{
		perror("fd");
		return (1);
	}
	if (ac != 5)
		exit(EXIT_FAILURE);
	//parse_args(ac, av, env);
	create_fork1(ac, av, env, fd);
	create_fork2(ac, &av[4], env, fd);
	close(fd[0]);
	close(fd[1]);
	return (0);
}
