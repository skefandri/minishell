/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:36:51 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/02 18:37:15 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	assign_less_than_type(t_token *token, char character, char next_char)
{
	if (character == next_char)
	{
		token->content = add_char(token->content, character);
		token->e_type = TOKEN_HERE_DOC;
	}
	else
		token->e_type = TOKEN_INFILE;
}

void	assign_greater_than_type(t_token *token, char character, char next_char)
{
	if (character == next_char)
	{
		token->content = add_char(token->content, character);
		token->e_type = TOKEN_APPEND;
	}
	else
		token->e_type = TOKEN_OUTFILE;
}

void	assign_pipe_type(t_token *token)
{
	token->e_type = TOKEN_PIPE;
}

void	assign_eof_type(t_token *token)
{
	token->e_type = TOKEN_EOF;
}

void	assign_string_type(t_token *token)
{
	token->e_type = TOKEN_STRING;
}
