/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 02:24:42 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/06 10:31:50 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_spaces(char **file)
{
	while (**file == ' ' || **file == '\t')
		(*file)++;
}

void	process_quotes(char **file, char *c)
{
	while (*file && **file)
	{
		if (*c == 0 && (**file == '\'' || **file == '\"'))
			*c = **file;
		else if (*c == **file)
			*c = 0;
		if ((**file == ' ' || **file == '\t') && *c == 0)
			break ;
		(*file)++;
	}
}

void	is_ambiguous(char *file)
{
	char	c;
	char	*str;

	c = 0;
	str = file;
	skip_spaces(&file);
	if (!*file)
	{
		printf("minishell: %s: ambiguous redirect\n", file);
		exit (1);
	}
	process_quotes(&file, &c);
	skip_spaces(&file);
	if (*file)
	{
		printf("minishell: %s: ambiguous redirect\n", file);
		exit (1);
	}
	remove_quotes(str);
}

void	close_and_open_infile(t_file *ptr)
{
	if (g_lob.in_fd)
		close(g_lob.in_fd);
	if (ptr->type != 4)
		is_ambiguous(ptr->filename);
	g_lob.in_fd = openfiles(ptr);
	if (g_lob.in_fd == -1)
	{
		perror(ptr->filename);
		exit(1);
	}
}

void	close_and_open_outfile(t_file *ptr)
{
	if (g_lob.out_fd != 1)
		close(g_lob.out_fd);
	is_ambiguous(ptr->filename);
	g_lob.out_fd = openfiles(ptr);
	if (g_lob.out_fd == -1)
	{
		perror(ptr->filename);
		exit(1);
	}
}
