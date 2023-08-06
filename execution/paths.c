/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 02:18:11 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/03 19:22:52 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_is_direct(char *cmd)
{
	if (stat_fun(cmd))
	{
		printf("./minishell %s: is a directory\n", cmd);
		exit (126);
	}
}

void	check_if_null(char *cmd)
{
	if (!cmd)
		error_check(1, NULL);
}

char	*cmd_path(char **paths, char *cmd, int i)
{
	char	*cmd_with_path;
	char	*tmp;

	check_if_null(cmd);
	if (!cmd[0])
		error_check(3, cmd);
	if (cmd[0] == '.' && cmd[1] == '/'
		&& !access(cmd, X_OK) && stat_fun(cmd) == 0)
		return (cmd);
	if (!access(cmd, F_OK) && cmd[0] == '/'
		&& stat_fun(cmd) == 0 && !access(cmd, X_OK))
		return (cmd);
	else
		check_is_direct(cmd);
	if (ft_strrchr(cmd, '/') == 1)
		error_check(2, cmd);
	while (paths && paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		cmd_with_path = ft_strjoin(tmp, cmd);
		if (!access(cmd_with_path, X_OK))
			return (cmd_with_path);
	}
	error_check (3, cmd);
	return (NULL);
}
