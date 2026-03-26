/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rnd_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 00:46:04 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/22 01:00:07 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


void	ft_find_tmp_name(uintptr_t *rnd)
{
	char	*filename;
	int		fd;

	while (1)
	{
		filename = ft_pseudo_random_filename(*rnd);
		if (!filename)
			exit(EXIT_FAILURE);
		fd = open(filename, O_RDONLY);
		if (fd == -1 && errno == ENOENT)
		{
			free(filename);
			break ;
		}
		if (fd != -1)
			close(fd);
		free(filename);
		(*rnd)++;
	}
}

uintptr_t	ft_get_rnd(void)
{
	uintptr_t	rnd;
	char		*ptr;

	ptr = malloc(1);
	if (!ptr)
		exit(EXIT_FAILURE);
	rnd = (uintptr_t)ptr;
	free(ptr);
	return (rnd);
}
