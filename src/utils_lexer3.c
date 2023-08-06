/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:39:12 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/03 18:40:51 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_token_content(char *line, t_token *token, int *i)
{
	char	c;

	c = 0;
	while (line[*i])
	{
		if (c == 0 && (line[*i] == '\'' || line[*i] == '\"'))
			c = line[*i];
		else if (c == line[*i])
			c = 0;
		if (c == 0 && (line[*i] == '<' || line[*i] == '>'
				|| line[*i] == '|' || line[*i] == ' ' || line[*i] == '\t'))
			break ;
		token->content = add_char(token->content, line[*i]);
		(*i)++;
	}
}

void	process_special_token(char *line, int *i, t_command **lexer)
{
	t_token	*token;

	token = NULL;
	if (line[*i] == '<' || line[*i] == '>')
	{
		token = create_token(line[*i], line[*i + 1]);
		if (line[*i] == line[*i + 1])
			(*i) += 2;
		else
			(*i)++;
		ft_lstadd_back(lexer, ft_lstnew(token));
	}
}

void	process_eof(char *line, int i, t_command **lexer)
{
	t_token	*token;

	if (line[i] == '\0')
	{
		token = create_token(line[i], line[i]);
		ft_lstadd_back(lexer, ft_lstnew(token));
	}
}

void	process_pipe(char *line, int i, t_command **lexer)
{
	t_token	*token;

	if (line[i] == '|')
	{
		token = create_token(line[i], line[i]);
		ft_lstadd_back(lexer, ft_lstnew(token));
	}
}

void	create_and_process_token(char *line, int *i, t_command **lexer)
{
	t_token	*token;

	token = init_tokens();
	fill_token_content(line, token, i);
	if (token->content)
	{
		token->e_type = TOKEN_STRING;
		ft_lstadd_back(lexer, ft_lstnew(token));
	}
	if (line[*i] == '<' || line[*i] == '>')
		process_special_token(line, i, lexer);
	else if (line[*i] == '|')
	{
		token = create_token(line[(*i)++], '\0');
		ft_lstadd_back(lexer, ft_lstnew(token));
	}
}
