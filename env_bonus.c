/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:19:15 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/21 14:44:54 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"
#include <stdlib.h>
#include <unistd.h>

char	*ft_combine_path(char *base, char *cmd)
{
	char	*new;
	size_t	len_base;
	size_t	len_cmd;

	len_base = ft_strlen(base);
	len_cmd = ft_strlen(cmd);
	new = malloc(sizeof(char) * (len_base + len_cmd + 2));
	if (!new)
		return (NULL);
	ft_memcpy(new, base, len_base);
	ft_memcpy(new + len_base, "/", 1);
	ft_memcpy(new + len_base + 1, cmd, len_cmd);
	new[len_base + len_cmd + 1] = '\0';
	return (new);
}

char	*ft_check_cmd(char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

char	*ft_try_paths(char **paths, char *cmd)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		full_path = ft_combine_path(paths[i], cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*ft_get_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*path;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_check_cmd(cmd));
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			if (!paths)
				return (NULL);
			path = ft_try_paths(paths, cmd);
			ft_free_arr(paths);
			if (path)
				return (path);
		}
		i++;
	}
	return (NULL);
}
