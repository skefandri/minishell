/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:02:59 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/06 10:58:18 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(t_envs *env)
{
	t_envs	*tmp;
	char	*str;

	tmp = env;
	str = getcwd(NULL, 0);
	if (!str)
	{
		while (tmp)
		{
			if (!ft_strncmp(tmp->env, "PWD", 3))
				printf("%s\n", tmp->value);
			tmp = tmp->next;
		}
	}
	else
		printf("%s\n", str);
	free(str);
}

void	add_to_env_if(char *str)
{
	t_envs	*node;
	t_envs	*tmp;

	tmp = g_lob.envs;
	node = ft_lstnew_env(str);
	while (tmp)
	{
		if (!ft_strcmp(tmp->env, node->env))
		{
			free(node->value);
			free(node->env);
			free(node);
			return ;
		}
		tmp = tmp->next;
	}
	ft_lstadd_back_env(&g_lob.envs, node);
}
