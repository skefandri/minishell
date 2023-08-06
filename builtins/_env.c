/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 12:10:05 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/06 12:10:07 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	_env(char **env)
{
	t_envs	*tmp;

	(void)env;
	tmp = g_lob.envs;
	while (tmp)
	{
		if (tmp->value)
		{
			printf("%s=", tmp->env);
			printf("%s\n", tmp->value);
		}
		tmp = tmp->next;
	}
}

void	error_message(char *str)
{
	write(2, str, ft_strlen(str));
}

void	err_export(char *str)
{
	error_message("minishell: export: ");
	error_message(str);
	error_message(": not a valid identifier\n");
}
