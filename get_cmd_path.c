/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsipile <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 17:40:15 by lsipile           #+#    #+#             */
/*   Updated: 2022/10/19 21:49:49 by lsipile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "pipex.h"

char	**get_path_str(char **envp)
{
	int		i;
	int		len;
	char	**path_cmd_sh;

	i = 0;
	while (envp[i])
	{
		len = ft_strlen(envp[i]);
		if (len > 4)
		{
			if (ft_strncmp("PATH", envp[i], 4) == 0)
				break ;
		}
		i++;
	}
	path_cmd_sh = ft_split(envp[i], ':');
	return (path_cmd_sh);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	**pathstr;
	char	*tmp;
	char	*cmd_path;

	i = 0;
	pathstr = get_path_str(envp);
	while (pathstr[i])
	{
		tmp = ft_strjoin(pathstr[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}
