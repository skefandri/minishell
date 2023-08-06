/* ************************************************************************** */
/*	                                                                       */
/*                                                        :::      ::::::::   */
/*   file_builting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 22:33:56 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/01 12:25:13 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_ambiguous_builting(char *file)
{
	char	c;
	char	*str;

	c = 0;
	str = file;
	skip_spaces(&file);
	if (!*file)
	{
		printf("minishell: %s: ambiguous redirect\n", file);
		g_lob.out_fd = -1;
		return (1);
	}
	process_quotes(&file, &c);
	skip_spaces(&file);
	if (*file)
	{
		printf("minishell: %s: ambiguous redirect\n", file);
		g_lob.out_fd = -1;
		return (1);
	}
	remove_quotes(str);
	return (0);
}

int	close_and_open_infile_builting(t_file *ptr)
{
	if (g_lob.in_fd)
		close(g_lob.in_fd);
	if (ptr->type != 4 && is_ambiguous_builting(ptr->filename))
		return (1);
	g_lob.in_fd = openfiles(ptr);
	if (g_lob.in_fd == -1)
	{
		perror(ptr->filename);
		return (1);
	}
	return (0);
}

int	close_and_open_outfile_builting(t_file *ptr)
{
	if (g_lob.out_fd != 1)
		close(g_lob.out_fd);
	if (is_ambiguous_builting(ptr->filename))
		return (1);
	g_lob.out_fd = openfiles(ptr);
	if (g_lob.out_fd == -1)
	{
		perror(ptr->filename);
		return (1);
	}
	return (0);
}

void	manage_file_builting(t_file *ptr)
{
	if (ptr->type == 1 || ptr->type == 4)
		close_and_open_infile_builting(ptr);
	if (ptr->type == 2 || ptr->type == 5)
		close_and_open_outfile_builting(ptr);
}

void	process_files_builting(t_file *ptr)
{
	while (ptr)
	{
		manage_file_builting(ptr);
		if (g_lob.in_fd == -1 || g_lob.out_fd == -1)
			break ;
		ptr = ptr->next;
	}
}
