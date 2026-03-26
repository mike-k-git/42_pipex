/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:44:05 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/21 14:42:11 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close(int pipe_fd[2], int io_fd[2])
{
	if (pipe_fd[0] >= 0)
		close(pipe_fd[0]);
	if (pipe_fd[1] >= 0)
		close(pipe_fd[1]);
	if (io_fd[0] >= 0)
		close(io_fd[0]);
	if (io_fd[1] >= 0)
		close(io_fd[1]);
}

void	ft_safe_dup2(int oldfd, int newfd, int pipe_fd[2], int io_fd[2])
{
	if (dup2(oldfd, newfd) == -1)
	{
		ft_close(pipe_fd, io_fd);
		ft_error_print("dup2", 1);
	}
}

void	ft_wait(pid_t pid_ids[2], int io_fd[2])
{
	int		status;

	if (pid_ids[0] != -1)
		waitpid(pid_ids[0], NULL, 0);
	waitpid(pid_ids[1], &status, 0);
	if (io_fd[1] == -1)
		exit(EXIT_FAILURE);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
}

void	ft_run_pipe(char **argv, char **envp, int io_fd[2], int pipe_fd[2])
{
	pid_t	pid_ids[2];

	pid_ids[0] = -1;
	if (io_fd[0] != -1)
	{
		ft_fork_exit(&pid_ids[0], pipe_fd, io_fd);
		if (pid_ids[0] == 0)
		{
			ft_safe_dup2(io_fd[0], STDIN_FILENO, pipe_fd, io_fd);
			ft_safe_dup2(pipe_fd[1], STDOUT_FILENO, pipe_fd, io_fd);
			ft_close(pipe_fd, io_fd);
			ft_exec_cmd(argv[2], envp, io_fd, pipe_fd);
		}
	}
	ft_fork_exit(&pid_ids[1], pipe_fd, io_fd);
	if (pid_ids[1] == 0 && io_fd[1] != -1)
	{
		ft_safe_dup2(pipe_fd[0], STDIN_FILENO, pipe_fd, io_fd);
		ft_safe_dup2(io_fd[1], STDOUT_FILENO, pipe_fd, io_fd);
		ft_close(pipe_fd, io_fd);
		ft_exec_cmd(argv[3], envp, io_fd, pipe_fd);
	}
	ft_close(pipe_fd, io_fd);
	ft_wait(pid_ids, io_fd);
}

int	main(int argc, char **argv, char **envp)
{
	int		io_fd[2];
	int		pipe_fd[2];

	if (argc != 5)
		exit(EXIT_FAILURE);
	ft_open_in_file(argv[1], &io_fd[0]);
	ft_open_out_file(argv[4], &io_fd[1]);
	if (pipe(pipe_fd) == -1)
		ft_error_print("pipe", 1);
	ft_run_pipe(argv, envp, io_fd, pipe_fd);
	return (0);
}
