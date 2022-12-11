/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsipile <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 22:17:57 by lsipile           #+#    #+#             */
/*   Updated: 2022/10/20 00:15:49 by lsipile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <stddef.h>

char	*ft_strcpy(char *dest, char *src);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
char	*get_cmd_path(char *cmd, char **envp);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *first, const char *second, size_t length);
int		cmd_exec(char *cmd_input, char **envp);
int		*file_opening(char *input, char *output);
int		file_id_copy(int to_stdin, int to_stdout);
void	child1_process(char *arg, char **env, int *ends, int *fd_file);
void	child2_process(char *arg, char **env, int *ends, int *fd_file);
void	closure_wait(int *f1, int *f2, pid_t *pid, int *status);
int		pipe_and_check(int *ends);
int		pid_and_check(pid_t pid);
int		check_arg(int argc);
#endif
