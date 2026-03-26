/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:00:53 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/18 18:45:00 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "get_next_line.h"

void	ft_open_in_file(char *filename, int *infile)
{
	*infile = open(filename, O_RDONLY);
	if (*infile == -1)
		ft_error_print(filename, 0);
}

void	ft_open_out_file(char *filename, int *outfile)
{
	*outfile = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*outfile == -1)
		ft_error_print(filename, 0);
}
