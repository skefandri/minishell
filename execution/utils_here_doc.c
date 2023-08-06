/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 08:43:25 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/03 23:04:54 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*remove_spaces(char *lexer)
{
	char	*str;
	int		i;

	i = 0;
	while (lexer[i] && lexer[i] != ' ')
		i++;
	str = my_malloc(i + 1);
	if (!str)
		return (0);
	i = 0;
	while (lexer[i] && lexer[i] != ' ')
	{
		str[i] = lexer[i];
		i++;
	}
	str [i] = '\0';
	return (str);
}

int	check_flag(t_file *tmp)
{
	int	flag;

	flag = 0;
	if (ft_strlen(tmp->filename) != ft_strlen(remove_quotes(tmp->filename)))
		flag = 1;
	return (flag);
}

char	*read_and_write(int flag, char *filename, int fd[2])
{
	char	*str;
	char	*pp;
	char	**ptr;

	while (1)
	{
		str = readline("> ");
		if (!str || !ft_strcmp(str, filename))
			break ;
		if (flag == 0)
		{
			pp = str;
			ptr = lst_to_envs(g_lob.envs);
			str = expand_result(pp, ptr, 1);
		}
		write(fd[1], str, ft_strlen(str));
		write(fd[1], "\n", 1);
	}
	return (str);
}
