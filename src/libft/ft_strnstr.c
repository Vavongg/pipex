/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:46:36 by ainthana          #+#    #+#             */
/*   Updated: 2025/04/01 11:47:40 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*found;

	i = 0;
	j = 0;
	if (!little[j])
		return ((char *) big);
	while (big[i] && i < len)
	{
		if (big[i] == little[0])
		{
			while (big[i + j] == little[j] && little[j] && i + j < len)
				j++;
			if (little[j] == '\0')
			{
				found = (char *) &big[i];
				return (found);
			}
		}
		j = 0;
		i++;
	}
	return (0);
}
