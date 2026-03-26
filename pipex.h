/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:25:48 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/21 14:46:40 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>

// Environment
char	*ft_get_cmd_path(char *cmd, char **envp);
void	ft_open_in_file(char *filename, int *infile);
void	ft_open_out_file(char *filename, int *outfile);

// Error handling
char	*ft_err_msg_copy(char *err);
void	ft_error_print(char *filename, int e);
void	ft_cmd_not_found(char *cmd);
void	ft_cmd_perm_denied(char *cmd, char *prefix, char *suffix);

// Utils
void	ft_free_arr(char **arr);

// Fork
void	ft_fork_exit(pid_t *pid, int pipe_fd[2], int io_fd[2]);
void	ft_close(int pipe_fd[2], int io_fd[2]);

// Exec
void	ft_exec_cmd(char *cmd, char **envp, int pipe_fd[2], int io_fd[2]);

// Expand
char	**ft_expand(char *s, char c);

#endif
