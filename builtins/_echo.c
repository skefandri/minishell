/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _echo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 12:09:53 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/06 12:09:56 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	contains_only_n(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	print_arguments(char **args, int k)
{
	int	i;

	i = 0;
	if (args[i])
	{
		printf("%s", args[i++]);
		while (args[i])
		{
			printf(" %s", args[i]);
			i++;
		}
	}
	if (!i || k)
		printf("\n");
}

void	process_options(char **args)
{
	int	i;

	i = 1;
	if (contains_only_n(args[i] + 1))
		print_arguments(args + 1, 1);
	else
	{
		while (args[i] && *args[i] == '-' && !contains_only_n(args[i] + 1))
			i++;
		print_arguments(args + i, 0);
	}
}

void	simple_echo(char **args)
{
	if (!args[1])
		printf("\n");
	else if (args[1][0] == '-')
		process_options(args);
	else
		print_arguments(args + 1, 1);
}
