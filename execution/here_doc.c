/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:41:15 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/10 18:39:34 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_child_process(int fd[2], t_file *tmp, int flag)
{
	signal(SIGINT, SIG_DFL);
	close(fd[0]);
	read_and_write(flag, tmp->filename, fd);
	close(fd[1]);
	exit(0);
}

int	handle_parent_process(int fd[2], int pid, t_file *tmp)
{
	close(fd[1]);
	wait(&pid);
	tmp->fd = fd[0];
	if (WIFSIGNALED(pid))
		return (3);
	return (0);
}

int	handle_file(t_data *lexer, int fd[2])
{
	t_file	*tmp;
	int		pid;
	int		flag;

	tmp = lexer->file;
	while (tmp)
	{
		if (tmp->type == 4)
		{
			flag = check_flag(tmp);
			pipe(fd);
			pid = fork();
			if (pid == 0)
				handle_child_process(fd, tmp, flag);
			else
			{
				if (handle_parent_process(fd, pid, tmp) == 3)
					return (3);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	iterate_files(t_data *lexer, int fd[2])
{
	while (lexer)
	{
		if (handle_file(lexer, fd) == 3)
			return (3);
		lexer = lexer->next;
	}
	return (0);
}

int	here_document(t_data *lexer)
{
	int	fd[2];

	return (iterate_files(lexer, fd));
}
