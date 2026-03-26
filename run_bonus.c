/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:58:36 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/21 11:50:41 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_wait(int num_cmds, int *pids, int *pipes, int io_fd[2])
{
	int	status;
	int	i;

	i = 0;
	while (i < num_cmds)
	{
		if (pids[i] != -1)
			waitpid(pids[i], &status, 0);
		i++;
	}
	free(pipes);
	free(pids);
	if (io_fd[1] == -1)
		exit(EXIT_FAILURE);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	exit(EXIT_FAILURE);
}

void	ft_close(int *pipes, int num_pipes, int io_fd[2])
{
	int	i;

	i = 0;
	while (i < num_pipes * 2)
	{
		if (pipes[i] != -1)
		{
			close(pipes[i]);
			i++;
		}
	}
	if (io_fd[0] != -1)
		close(io_fd[0]);
	if (io_fd[1] != -1)
		close(io_fd[1]);
}

void	ft_redirect(int pipe_num, int *pipes, int io_fd[2], int num_cmds)
{
	int	err;

	err = 0;
	if (pipe_num == 0)
		err = dup2(io_fd[0], STDIN_FILENO);
	else
		err = dup2(pipes[(pipe_num - 1) * 2], STDIN_FILENO);
	if (pipe_num == num_cmds - 1 && io_fd[1] != -1 && err != -1)
		err = dup2(io_fd[1], STDOUT_FILENO);
	else if (err != -1)
		err = dup2(pipes[pipe_num * 2 + 1], STDOUT_FILENO);
	if (err == -1)
	{
		ft_close(pipes, num_cmds - 1, io_fd);
		perror("dup2");
		exit(EXIT_FAILURE);
	}
}

int	ft_check_io(pid_t *pids, int io_fd[2], int *i)
{
	if (*i == 0 && io_fd[0] == -1)
	{
		pids[*i] = -1;
		*i = *i + 1;
		return (1);
	}
	return (0);
}

void	ft_run(int argc, int io_fd[2], char **envp, char **argv)
{
	int		*pipes;
	pid_t	*pids;
	int		i;
	int		cmd_offset;

	cmd_offset = ft_cmd_offset(argc, argv);
	ft_init(argc - 4 - (cmd_offset - 2), &pipes, &pids);
	ft_create_pipes(argc - 4 - (cmd_offset - 2), pipes, pids);
	i = 0;
	while (i < argc - cmd_offset - 1)
	{
		if (ft_check_io(pids, io_fd, &i))
			continue ;
		pids[i] = ft_fork(pipes, pids);
		if (pids[i] == 0 && !(i == argc - cmd_offset - 2 && io_fd[1] == -1))
		{
			ft_redirect(i, pipes, io_fd, argc - cmd_offset - 1);
			ft_close(pipes, argc - 4 - (cmd_offset - 2), io_fd);
			ft_free_pipes_and_pids(&pipes, &pids);
			ft_exec_cmd(argv[i + cmd_offset], envp);
		}
		i++;
	}
	ft_close(pipes, argc - 4 - (cmd_offset - 2), io_fd);
	ft_wait(argc - cmd_offset - 1, pids, pipes, io_fd);
}
