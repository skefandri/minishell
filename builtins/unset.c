/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 12:10:17 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/11 08:39:56 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_envs	*ft_lstlastt(t_envs *lst)
{
	t_envs	*head;

	if (lst == NULL)
		return (NULL);
	while (lst)
	{
		head = lst;
		lst = lst -> next;
	}
	return (head);
}

void	print_message(char *str)
{
	ft_putstr_fd("minishell: unset:", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	return ;
}

void	ft_remove(char *str)
{
	t_envs	*del;
	t_envs	*tmp;

	tmp = g_lob.envs;
	if (!is_valid_identifier(str))
		print_message(str);
	if (tmp && !ft_strcmp(tmp->env, str))
	{
		g_lob.envs = tmp->next;
		return ;
	}
	while (tmp && tmp->next)
	{
		if (!ft_strcmp(tmp->next->env, str))
		{
			del = tmp->next;
			tmp->next = del->next;
			return ;
		}
		tmp = tmp->next;
	}
}

void	re_unset(char **args)
{
	int	i;

	i = 0;
	if (!args[i])
		return ;
	while (args[i])
	{
		ft_remove(args[i]);
		i++;
	}
}
