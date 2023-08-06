/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:04:32 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/06 12:08:50 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_value(char	*value)
{
	int		i;
	char	*s;

	i = 0;
	while (value[i] && value[i] != '=')
		i++;
	if (!value[i])
		return (NULL);
	s = ft_strdup(value + i + 1);
	return (s);
}

char	*get_env_plus(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '+')
			j = i;
		i++;
	}
	new = ft_substr(str, 0, j);
	return (new);
}

void	declare_envs(void)
{
	t_envs	*tmp;

	tmp = g_lob.envs;
	while (tmp)
	{
		if (tmp->value)
		{
			printf("declare -x %s=", tmp->env);
			printf("\"%s\"\n", tmp->value);
		}
		else
			printf("declare -x %s\n", tmp->env);
		tmp = tmp->next;
	}
	return ;
}

void	process_args(char *arg)
{
	if (is_valid_identifier(arg) == 2)
		join_values(arg);
	else if (!ft_strchr(arg, '=') && is_valid_identifier(arg))
		add_to_env_if(arg);
	else if (is_valid_identifier(arg))
	{
		add_to_env(arg);
		g_lob.exit_status = 0;
	}
	else
	{
		err_export(arg);
		g_lob.exit_status = 1;
	}
}

void	re_export(char **args)
{
	int	i;

	i = 0;
	if (!args[i])
	{
		declare_envs();
		g_lob.exit_status = 0;
		return ;
	}
	while (args[i])
	{
		process_args(args[i]);
		i++;
	}
}
