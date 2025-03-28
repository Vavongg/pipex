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

void	create_file(int ac, char **av)
{
	(void)ac;
	int fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
	{
        perror(av[4]);
        return ;
    }
    close(fd);
}
