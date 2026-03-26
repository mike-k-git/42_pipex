/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:52:53 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/21 14:46:20 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "pipex.h"

void	ft_error_print(char *filename, int e)
{
	ft_dprintf(2, "%s: %s: %s\n", "pipex", filename, strerror(errno));
	if (e == 1)
		exit(EXIT_FAILURE);
}

void	ft_cmd_not_found(char *cmd)
{
	char	*message;
	size_t	cmd_len;
	size_t	message_len;
	char	*output;

	message = ": command not found\n";
	if (!cmd || ft_strlen(cmd) == 0)
		cmd = "''";
	cmd_len = ft_strlen(cmd);
	message_len = ft_strlen(message);
	output = malloc(sizeof(char) * (message_len + cmd_len + 2));
	if (!output)
		exit(EXIT_FAILURE);
	ft_strlcpy(output, cmd, cmd_len + 1);
	ft_strlcpy(output + cmd_len, message, message_len + 1);
	write(2, output, ft_strlen(output));
	free(output);
}

void	ft_cmd_perm_denied(char *cmd, char *prefix, char *suffix)
{
	size_t	cmd_len;
	size_t	prefix_len;
	size_t	suffix_len;
	char	*output;

	if (!cmd || ft_strlen(cmd) == 0)
		cmd = "''";
	cmd_len = ft_strlen(cmd);
	prefix_len = ft_strlen(prefix);
	suffix_len = ft_strlen(suffix);
	output = malloc(sizeof(char) * (prefix_len + suffix_len + cmd_len + 3));
	if (!output)
		exit(EXIT_FAILURE);
	ft_strlcpy(output, prefix, prefix_len + 1);
	ft_strlcpy(output + prefix_len, cmd, cmd_len + 1);
	ft_strlcpy(output + prefix_len + cmd_len, suffix, suffix_len + 1);
	write(2, output, ft_strlen(output));
	free(output);
}
