/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_bonus_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:09:30 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/21 12:19:45 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <stdint.h>

char	*ft_pseudo_random_filename(uintptr_t rnd)
{
	char	*fn;
	char	*id_c;

	id_c = ft_itoa((long)rnd);
	if (id_c == NULL)
		return (NULL);
	fn = malloc(sizeof(char) * (ft_strlen(id_c) + 6 + 6 + 1));
	if (fn == NULL)
		ft_error_print("pipex: generate filename: ", 1);
	ft_memcpy(fn, "/tmp/t", 6);
	ft_memcpy(fn + 6, id_c, ft_strlen(id_c));
	ft_memcpy(fn + 6 + ft_strlen(id_c), "-pipex", 6);
	fn[ft_strlen(id_c) + 12] = '\0';
	free(id_c);
	return (fn);
}

void	ft_safe_unlink(uintptr_t rnd)
{
	char	*fn;

	fn = ft_pseudo_random_filename(rnd);
	if (unlink(fn) == -1)
	{
		perror("pipex: unlink");
		free(fn);
		exit(EXIT_FAILURE);
	}
	free(fn);
}

void	ft_safe_write(int tmp_fd, char *line, uintptr_t rnd)
{
	int	bytes_written;

	bytes_written = write(tmp_fd, line, ft_strlen(line));
	if (bytes_written == -1)
	{
		free(line);
		close(tmp_fd);
		ft_safe_unlink(rnd);
		perror("pipex: write");
		exit(EXIT_FAILURE);
	}
}

void	ft_open_in_heredoc_file(int *infile, uintptr_t rnd)
{
	char	*fn;

	fn = ft_pseudo_random_filename(rnd);
	if (!fn)
		ft_error_print("pipex: generate filename: ", 1);
	*infile = open(fn, O_RDONLY);
	if (*infile == -1)
	{
		free(fn);
		ft_error_print("pipex: open temporary file:", 1);
	}
	free(fn);
}
