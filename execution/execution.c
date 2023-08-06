/* ************************************************************************** */
/*					                                                        */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:11:07 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/01 00:18:24 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	setup_and_exec(t_data *proc, int index, char **args)
{
	args = lst_to_args(proc->cmd);
	setup_signal_handlers();
	process_files(proc->file);
	manage_duplications_and_closing();
	if (proc && proc->cmd)
		index = is_builtin(proc->cmd->cmd);
	if (index)
	{
		exec_builtin(args, index);
		exit(g_lob.exit_status);
	}
	else
		exec_cmd_or_builtin(proc, args);
}

void	exec_process_loop(t_data *proc, int pass, int index)
{
	char	**args;

	args = NULL;
	while (proc)
	{
		g_lob.in_fd = pass;
		g_lob.out_fd = 1;
		index = 0;
		setup_pipe_and_fork(proc, &pass);
		if (!proc->pid)
			setup_and_exec(proc, index, args);
		cleanup_after_exec();
		proc = proc->next;
	}
}

void	exec_process(t_data *proc)
{
	int	pass;
	int	index;

	index = 0;
	pass = 0;
	g_lob.fd[0] = 0;
	g_lob.fd[1] = 1;
	if (check_builtins(proc))
		return ;
	exec_process_loop(proc, pass, index);
}

void	execution(t_data *data)
{
	t_data	*tmp;

	g_lob.in_fd = 0;
	g_lob.out_fd = 1;
	exec_process(data);
	tmp = data;
	while (tmp)
	{
		waitpid(tmp->pid, &g_lob.exit_status, 0);
		if (WIFSIGNALED(g_lob.exit_status))
		{
			if (WTERMSIG(g_lob.exit_status) == SIGQUIT)
				g_lob.exit_status = 131;
			else if (WTERMSIG(g_lob.exit_status) == SIGINT)
				g_lob.exit_status = 130;
		}
		else
			g_lob.exit_status = WEXITSTATUS(g_lob.exit_status);
		tmp = tmp->next;
	}
}
