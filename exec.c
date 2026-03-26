/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:34:20 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/21 11:34:45 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

void	ft_exit(char *cmd, int io_fd[2], int pipe_fd[2])
{
	if (errno == ENOENT)
	{
		ft_close(io_fd, pipe_fd);
		exit(127);
	}
	else if (errno == EACCES)
	{
		ft_cmd_perm_denied(cmd, "pipex: ", ": Permission denied\n");
		ft_close(io_fd, pipe_fd);
		exit(126);
	}
	else
	{
		ft_close(io_fd, pipe_fd);
		exit(1);
	}
}

void	ft_exec_cmd(char *cmd, char **envp, int io_fd[2], int pipe_fd[2])
{
	char	**args;
	char	*cmd_path;

	args = ft_expand(cmd, ' ');
	if (!args)
		exit(EXIT_FAILURE);
	cmd_path = ft_get_cmd_path(args[0], envp);
	if (!cmd_path)
	{
		ft_free_arr(args);
		ft_cmd_not_found(cmd);
		exit(127);
	}
	if (execve(cmd_path, args, envp) == -1)
	{
		ft_free_arr(args);
		free(cmd_path);
		ft_exit(cmd, io_fd, pipe_fd);
	}
}
