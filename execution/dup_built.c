/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_built.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 08:42:00 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/06 12:09:12 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_whitespaces(char **str)
{
	while (**str == ' ' || **str == '\t')
		(*str)++;
}

void	validate_string(char **str, char *original_str)
{
	char	c;

	c = 0;
	if (!**str)
	{
		printf("minishell: %s: ambiguous redirect\n", *str);
		exit(1);
	}
	while (*str && **str)
	{
		if (c == 0 && (**str == '\'' || **str == '\"'))
			c = **str;
		else if (c == **str)
			c = 0;
		if ((**str == ' ' || **str == '\t') && c == 0)
			break ;
		(*str)++;
	}
	skip_whitespaces(str);
	if (**str)
	{
		printf("minishell: %s: ambiguous redirect\n", *str);
		exit(1);
	}
	remove_quotes(original_str);
}

void	ambiguous(char *file)
{
	char	*str;

	str = file;
	skip_whitespaces(&file);
	validate_string(&file, str);
}

void	_cont_check_builts(t_data *proc, int index)
{
	char	**args;
	int		saveout;

	if (g_lob.in_fd)
		close(g_lob.in_fd);
	if (g_lob.out_fd != 1)
	{
		saveout = dup(1);
		dup2(g_lob.out_fd, 1);
		close(g_lob.out_fd);
	}
	args = lst_to_args(proc->cmd);
	exec_builtin(args, index);
	if (g_lob.out_fd != 1)
	{
		close(1);
		dup2(saveout, 1);
		close(saveout);
	}
	g_lob.in_fd = 0;
	g_lob.out_fd = 1;
}

int	check_builtins(t_data *proc)
{
	int		index;

	index = 0;
	if (proc && proc->cmd)
		index = is_builtin(proc->cmd->cmd);
	if (proc && !proc->next && index)
	{
		g_lob.in_fd = 0;
		g_lob.out_fd = 1;
		process_files_builting(proc->file);
		if (g_lob.in_fd == -1 || g_lob.out_fd == -1)
		{
			if (g_lob.in_fd > 2)
				close(g_lob.in_fd);
			if (g_lob.out_fd > 2)
				close(g_lob.out_fd);
			g_lob.in_fd = 0;
			g_lob.out_fd = 1;
			g_lob.exit_status = 1;
			return (1);
		}
		_cont_check_builts(proc, index);
		return (1);
	}
	return (0);
}
