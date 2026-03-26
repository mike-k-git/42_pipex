/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:38:55 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/21 14:43:30 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_fork_exit(pid_t *pid, int pipe_fd[2], int io_fd[2])
{
	*pid = fork();
	if (*pid == -1)
	{
		ft_close(pipe_fd, io_fd);
		exit(EXIT_FAILURE);
	}
}
