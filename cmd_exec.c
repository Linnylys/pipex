/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsipile <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 22:42:11 by lsipile           #+#    #+#             */
/*   Updated: 2022/10/20 00:18:48 by lsipile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <errno.h>
#include <stdio.h>
#include "pipex.h"

int	cmd_exec(char *cmd_input, char **envp)
{
	char	**cmd;
	char	*cmd_path;
	int		res;

	cmd = ft_split(cmd_input, ' ');
	if (!cmd)
	{
		free(cmd);
		perror("Command no exist");
		return (1);
	}
	cmd_path = get_cmd_path(cmd[0], envp);
	if (!cmd_path)
	{
		free(cmd);
		perror("Command Path");
		free(cmd_path);
		return (1);
	}
	res = execve(cmd_path, cmd, envp);
	return (res);
}

int	pipe_and_check(int *ends)
{
	int	flag;

	flag = pipe(ends);
	if (flag == -1)
	{
		perror("pipe_and_check");
		return (1);
	}
	return (0);
}

int	pid_and_check(pid_t pid)
{
	if (pid == -1)
	{
		perror("pid_and_check");
		return (1);
	}
	return (0);
}

int	check_arg(int argc)
{
	if (argc != 5)
	{
		write(2, "Uncorrect number arguments", 26);
		return (1);
	}
	return (0);
}
