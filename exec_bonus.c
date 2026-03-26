/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:57:46 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/18 12:04:45 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_exit(char *cmd)
{
	if (errno == ENOENT)
		exit(127);
	else if (errno == EACCES)
	{
		ft_cmd_perm_denied(cmd, "pipex: ", ": Permission denied\n");
		exit(126);
	}
	else
		exit(1);
}

void	ft_exec_cmd(char *cmd, char **envp)
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
		ft_exit(cmd);
	}
}
