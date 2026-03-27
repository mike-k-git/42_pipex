/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:17:35 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/21 12:19:19 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "get_next_line.h"
#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_open_in_file(char *filename, int *infile)
{
	*infile = open(filename, O_RDONLY);
	if (*infile == -1)
		ft_error_print(filename, 0);
}

void	ft_open_in_tmp_file(int *fd, uintptr_t rnd)
{
	char	*fn;

	fn = ft_pseudo_random_filename(rnd);
	*fd = open(fn, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*fd == -1)
	{
		free(fn);
		ft_error_print("pipex: open temporary file:", 1);
	}
	free(fn);
}

void	ft_open_out_file(char *filename, int *outfile)
{
	*outfile = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*outfile == -1)
		ft_error_print(filename, 0);
}

void	ft_open_out_file_append(char *filename, int *outfile)
{
	*outfile = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*outfile == -1)
		ft_error_print(filename, 0);
}

void	ft_here_doc(char *limiter, int *read_end, uintptr_t rnd)
{
	int		tmp_fd;
	char	*line;

	ft_open_in_tmp_file(&tmp_fd, rnd);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
      gnl_clear(STDIN_FILENO);
			break ;
		}
		ft_safe_write(tmp_fd, line, rnd);
		free(line);
	}
	close(tmp_fd);
	ft_open_in_heredoc_file(&tmp_fd, rnd);
	ft_safe_unlink(rnd);
	*read_end = tmp_fd;
}
