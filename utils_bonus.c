/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:20:37 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/18 19:09:12 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft.h"
#include <stdlib.h>

void	ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	ft_cmd_offset(int argc, char **argv)
{
	if (argc > 1 && ft_strncmp(argv[1], "here_doc", 9) == 0)
		return (3);
	return (2);
}
