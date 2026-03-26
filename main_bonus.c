/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:44:05 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/22 00:59:33 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft.h"
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	int			io_fd[2];
	uintptr_t	rnd;

	if (argc < 5)
		exit(EXIT_FAILURE);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		if (argc < 6)
			exit(EXIT_FAILURE);
		rnd = ft_get_rnd();
		ft_here_doc(argv[2], &io_fd[0], rnd);
		ft_open_out_file_append(argv[argc - 1], &io_fd[1]);
	}
	else
	{
		ft_open_in_file(argv[1], &io_fd[0]);
		ft_open_out_file(argv[argc - 1], &io_fd[1]);
	}
	ft_run(argc, io_fd, envp, argv);
}
