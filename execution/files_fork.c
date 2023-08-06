/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 02:23:15 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/06 12:09:30 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	openfiles(t_file *ptr)
{
	int	fd;

	fd = -1;
	if (ptr->type == 1)
		fd = open(ptr->filename, O_RDONLY);
	else if (ptr->type == 2)
		fd = open(ptr->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (ptr->type == 5)
		fd = open(ptr->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (ptr->type == 4)
		fd = ptr->fd;
	return (fd);
}

void	setup_pipe_and_fork(t_data *proc, int *pass)
{
	if (proc->next)
	{
		pipe(g_lob.fd);
		*pass = g_lob.fd[0];
		g_lob.out_fd = g_lob.fd[1];
	}
	proc->pid = fork();
	if (proc->pid == -1)
		perror("fork");
}

void	setup_signal_handlers(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	process_files(t_file *ptr)
{
	while (ptr)
	{
		manage_file(ptr);
		ptr = ptr->next;
	}
}

void	manage_file(t_file *ptr)
{
	if (ptr->type == 1 || ptr->type == 4)
		close_and_open_infile(ptr);
	if (ptr->type == 2 || ptr->type == 5)
		close_and_open_outfile(ptr);
}
