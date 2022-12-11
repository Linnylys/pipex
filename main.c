/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsipile <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:20:26 by lsipile           #+#    #+#             */
/*   Updated: 2022/10/20 00:19:44 by lsipile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid[2];
	int		ends[2];
	int		*fd_file;
	int		status[2];

	if (check_arg(argc) || pipe_and_check(ends))
		return (1);
	fd_file = file_opening(argv[1], argv[4]);
	pid[0] = fork();
	if (pid_and_check(pid[0]) || fd_file == NULL)
		return (1);
	else if (pid[0] == 0)
		child1_process(argv[2], envp, ends, fd_file);
	else if (pid[0] > 0)
	{
		pid[1] = fork();
		if (pid_and_check(pid[1]))
			return (1);
		else if (pid[1] == 0)
			child2_process(argv[3], envp, ends, fd_file);
		else if (pid[1] > 0)
			closure_wait(ends, fd_file, pid, status);
	}
	return (0);
}
