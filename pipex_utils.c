/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsipile <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 23:22:36 by lsipile           #+#    #+#             */
/*   Updated: 2022/10/19 21:56:30 by lsipile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "pipex.h"

int	*file_opening(char *input, char *output)
{
	int	*fd_file;

	fd_file = malloc(2 * sizeof(int));
	if (fd_file == NULL)
		return (NULL);
	fd_file[0] = open(input, O_RDONLY);
	if (fd_file[0] == -1)
	{
		perror("file_opening input");
		return (NULL);
	}
	fd_file[1] = open(output, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_file[1] == -1)
	{
		perror("file_opening output");
		return (NULL);
	}
	return (fd_file);
}

void	closure_wait(int *f1, int *f2, pid_t *pid, int *status)
{
	if (f1[0] >= 0)
		close(f1[0]);
	if (f1[1] >= 0)
		close(f1[1]);
	if (f2 != NULL)
	{
		if (f2[0] >= 0)
			close(f2[0]);
		if (f2[1] >= 0)
			close(f2[1]);
		free(f2);
	}
	if (pid != NULL && status != NULL)
	{
		waitpid(pid[0], &status[0], 0);
		waitpid(pid[1], &status[1], 0);
	}
}

int	file_id_copy(int to_stdin, int to_stdout)
{
	if (dup2(to_stdin, 0) == -1)
	{
		perror("Stdin ");
		return (1);
	}
	if (dup2(to_stdout, 1) == -1)
	{
		perror("Stdout ");
		return (1);
	}
	return (0);
}

void	child1_process(char *arg, char **env, int *ends, int *fd_file)
{
	file_id_copy(fd_file[0], ends[1]);
	closure_wait(ends, NULL, NULL, NULL);
	cmd_exec(arg, env);
}

void	child2_process(char *arg, char **env, int *ends, int *fd_file)
{
	file_id_copy(ends[0], fd_file[1]);
	closure_wait(ends, NULL, NULL, NULL);
	cmd_exec(arg, env);
}
