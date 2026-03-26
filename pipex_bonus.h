/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:25:48 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/22 01:02:00 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <sys/types.h>

// Environment
char		*ft_get_cmd_path(char *cmd, char **envp);

// Comand execution
void		ft_exec_cmd(char *cmd, char **envp);

// Input/Output
void		ft_open_in_file(char *filename, int *infile);
void		ft_open_out_file(char *filename, int *outfile);
void		ft_open_out_file_append(char *filename, int *outfile);
void		ft_here_doc(char *limiter, int *read_end, uintptr_t rnd);
void		ft_safe_unlink(uintptr_t rnd);
void		ft_safe_write(int tmp_fd, char *line, uintptr_t rnd);
char		*ft_pseudo_random_filename(uintptr_t rnd);
void		ft_open_in_heredoc_file(int *infile, uintptr_t rnd);

// Error handling
char		*ft_err_msg_copy(char *err);
void		ft_error_print(char *filename, int e);
void		ft_cmd_not_found(char *cmd);
void		ft_cmd_perm_denied(char *cmd, char *prefix, char *suffix);

// Utils
void		ft_free_arr(char **arr);
int			ft_cmd_offset(int argc, char **argv);

// Run
void		ft_run(int argc, int io_fd[2], char **envp, char **argv);

// Pipes utils
void		ft_init(int num_pipes, int **pipes, int **pids);
void		ft_create_pipes(int num_pipes, int *pipes, int *pids);
int			ft_fork(int *pipes, int *pids);
void		ft_free_pipes_and_pids(int **pipes, pid_t **pids);

// RND
uintptr_t	ft_get_rnd(void);

// Expand
char	**ft_expand(char *s, char c);

#endif
