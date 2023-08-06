/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 14:09:06 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/06 10:57:51 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isalnums(int an)
{
	if ((an >= 48 && an <= 57) || (an >= 65 && an <= 90)
		|| (an >= 95 && an <= 122))
		return (1);
	else
		return (0);
}

int	is_valid_identifier(char *str)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strchr(str, '='))
		j = ft_strlen(str) - ft_strlen(ft_strchr(str, '='));
	else
		j = ft_strlen(str);
	if (!str[i])
		return (0);
	if (!(str[i] >= 'a' && str[i] <= 'z')
		&& !(str[i] >= 'A' && str[i] <= 'Z') && str[i] != '_')
		return (0);
	while (i < j)
	{
		if (!ft_isalnums(str[i]) && str[i] != '_')
		{
			if (str[i] == '+' && str[i + 1] == '=')
				return (2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_lstsize_envs(t_envs *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	add_to_env(char *str)
{
	t_envs	*node;
	t_envs	*tmp;

	tmp = g_lob.envs;
	node = ft_lstnew_env(str);
	while (tmp)
	{
		if (!ft_strcmp(tmp->env, node->env))
		{
			free(tmp->value);
			tmp->value = node->value;
			free(node->env);
			free(node);
			return ;
		}
		tmp = tmp->next;
	}
	ft_lstadd_back_env(&g_lob.envs, node);
}

void	join_values(char *str)
{
	t_envs	*node;
	t_envs	*tmp;

	tmp = g_lob.envs;
	node = ft_lstnew_plus(str);
	while (tmp)
	{
		if (!ft_strncmp(tmp->env, node->env, ft_strlen(tmp->env)))
		{
			if (tmp->value)
				tmp->value = ft_strjoin(tmp->value, node->value);
			else
				tmp->value = ft_strdup(node->value);
			free(node->value);
			free(node->env);
			free(node);
			return ;
		}
		tmp = tmp->next;
	}
	ft_lstadd_back_env(&g_lob.envs, node);
}
