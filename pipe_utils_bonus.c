/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:01:34 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/21 11:50:47 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <unistd.h>
#include <stdlib.h>

int	ft_fork(int *pipes, int *pids)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		free(pipes);
		free(pids);
		ft_error_print("fork", 1);
	}
	return (pid);
}

void	ft_create_pipes(int num_pipes, int *pipes, int *pids)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipes + i * 2) == -1)
		{
			free(pipes);
			free(pids);
			ft_error_print("pipe", 1);
		}
		i++;
	}
}

void	ft_init(int num_pipes, int **pipes, int **pids)
{
	*pipes = malloc(sizeof(int) * 2 * num_pipes);
	if (!*pipes)
		exit(EXIT_FAILURE);
	*pids = malloc(sizeof(pid_t) * (num_pipes + 1));
	if (!*pids)
	{
		free(*pipes);
		exit(EXIT_FAILURE);
	}
}

void	ft_free_pipes_and_pids(int **pipes, pid_t **pids)
{
	free(*pipes);
	*pipes = NULL;
	free(*pids);
	*pids = NULL;
}
