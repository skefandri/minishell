/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:38:34 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/02 18:43:25 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	assign_type(t_token *token, char character, char next_char)
{
	if (character == '<')
		assign_less_than_type(token, character, next_char);
	else if (character == '>')
		assign_greater_than_type(token, character, next_char);
	else if (character == '|')
		assign_pipe_type(token);
	else if (character == '\0')
		assign_eof_type(token);
	else
		assign_string_type(token);
}

t_token	*init_token(char character)
{
	t_token	*token;

	token = my_malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = add_char(NULL, character);
	return (token);
}

t_token	*create_token(char character, char next_char)
{
	t_token	*token;

	token = init_token(character);
	if (!token)
		return (NULL);
	assign_type(token, character, next_char);
	return (token);
}

t_token	*init_tokens(void)
{
	t_token	*token;

	token = my_malloc(sizeof(t_token));
	token->content = NULL;
	return (token);
}

void	skip_whitespace(char *line, int *i)
{
	while (line[*i] == '\n' || line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}
