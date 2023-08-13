/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:14:34 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/08 22:22:32 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*initialize_char(char c)
{
	char	*new;

	new = my_malloc(2);
	if (!new)
		return (NULL);
	new[0] = c;
	new[1] = '\0';
	return (new);
}

char	*append_char(char *str, char c)
{
	int		i;
	char	*new;

	new = my_malloc(ft_strlen(str) + 2);
	if (!new)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = c;
	new[i + 1] = '\0';
	free(str);
	return (new);
}

char	*add_char(char *str, char c)
{
	if (!str)
		return (initialize_char(c));
	else
		return (append_char(str, c));
}

void	process_tokens(char *line, t_command **lexer)
{
	int	i;

	i = 0;
	while (line[i])
	{
		skip_whitespace(line, &i);
		if (!line[i])
			break ;
		create_and_process_token(line, &i, lexer);
	}
	process_eof(line, i, lexer);
}
