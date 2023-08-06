/* ************************************************************************** */
/*		                                                                    */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:18:05 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/03 18:24:02 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_syntax_error(t_command *current)
{
	printf("syntax error near unexpected token %s\n", current->content->content);
	g_lob.exit_status = 258;
}

int	check_file_tokens(t_command *current)
{
	if (current->content->e_type == TOKEN_INFILE
		|| current->content->e_type == TOKEN_OUTFILE
		|| current->content->e_type == TOKEN_HERE_DOC
		|| current->content->e_type == TOKEN_APPEND)
	{
		if (!current->next || current->next->content->e_type != TOKEN_STRING)
		{
			handle_syntax_error(current);
			return (1);
		}
	}
	return (0);
}

int	check_pipe_tokens(t_command *current)
{
	if (current->content->e_type == TOKEN_PIPE)
	{
		if (!current->next->content || !current->next
			|| current->next->content->e_type == TOKEN_PIPE
			|| current->next->content->e_type == TOKEN_EOF)
		{
			handle_syntax_error(current);
			return (1);
		}
	}
	return (0);
}

int	check_syntax_errors(t_command *lexer)
{
	t_command	*current;

	current = lexer;
	if (!lexer)
		return (0);
	if (current->content->e_type == TOKEN_PIPE)
	{
		handle_syntax_error(current);
		return (1);
	}
	while (current)
	{
		if (check_file_tokens(current) || check_pipe_tokens(current))
			return (1);
		current = current->next;
	}
	return (0);
}

int	check_quotes(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i];
			i++;
			while (input[i] && input[i] != quote)
				i++;
			if (!input[i])
			{
				printf("syntax error near unexpected token quotes \n");
				g_lob.exit_status = 258;
				return (1);
			}
		}
		i++;
	}
	return (0);
}
