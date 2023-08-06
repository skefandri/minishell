/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 02:25:32 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/06 12:09:22 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	manage_duplications_and_closing(void)
{
	if (g_lob.in_fd > 2)
	{
		dup2(g_lob.in_fd, 0);
		close(g_lob.in_fd);
	}
	if (g_lob.out_fd > 2)
	{
		dup2(g_lob.out_fd, 1);
		close(g_lob.out_fd);
	}
	if (g_lob.fd[0] != 0)
		close(g_lob.fd[0]);
}

void	exec_cmd_or_builtin(t_data *proc, char **args)
{
	char	**ptr;

	if (proc->cmd)
	{
		ptr = lst_to_envs(g_lob.envs);
		proc->cmd->cmd = cmd_path(_paths(ptr), args[0], -1);
		execve(proc->cmd->cmd, args, ptr);
		perror(proc->cmd->cmd);
		exit(1);
	}
	exit(0);
}

void	cleanup_after_exec(void)
{
	if (g_lob.in_fd > 2)
		close(g_lob.in_fd);
	if (g_lob.out_fd > 2)
		close(g_lob.out_fd);
}
