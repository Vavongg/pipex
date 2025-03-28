/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:31:17 by ainthana          #+#    #+#             */
/*   Updated: 2025/03/28 18:08:46 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	parse_args(int ac, char **av, char **env)
{
	(void)ac;
    if (access(av[1], R_OK) == -1)
    {
        perror(av[1]);
        exit(EXIT_FAILURE);
    }
    if (!is_valid_command(av[2], env) || !is_valid_command(av[3], env))
    {
        ft_printf("Invalid command");
        exit(127);
    }
}

int	is_valid_command(char *cmd, char **env)
{
	(void)env;
    if (access(cmd, X_OK) == 0)
		return 1;
    else
		return 0;
}
