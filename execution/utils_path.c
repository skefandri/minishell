/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 02:19:31 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/08 14:57:13 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*_path(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		if (ft_strncmp(p[i], "PATH=", 5) == 0)
			return (p[i] + 5);
		i++;
	}
	return (NULL);
}

char	**_paths(char **p)
{
	char	**paths;

	paths = ft_split(_path(p), ':');
	return (paths);
}

int	stat_fun(char *str)
{
	struct stat	s;

	if (stat(str, &s) == 0)
	{
		if (S_ISDIR(s.st_mode))
			return (1);
	}
	return (0);
}

void	error_check(int a, char *str)
{
	if (a == 1)
		printf("%c", '\0');
	if (a == 2)
	{
		perror(str);
		if (str[0] == '.')
			exit(127);
		else
			exit (126);
	}
	if (a == 3)
	{
		write(2, "minishell: ", 12);
		write(2, str, ft_strlen(str));
		write (2, ": command not found\n", 21);
	}
	exit(127);
}
