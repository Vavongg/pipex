/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:22:11 by ainthana          #+#    #+#             */
/*   Updated: 2025/03/28 17:45:30 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av, char **env)
{
	if (ac != 5)
		exit(EXIT_FAILURE);
	parse_args(ac, av);
	create_file(ac, &av[4]);
	return (0);
}
