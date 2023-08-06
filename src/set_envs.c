/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 14:02:17 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/02 18:49:47 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_envs	*set_envs(char **av)
{
	int			i;
	t_envs		*head;
	t_envs		*tmp;

	head = NULL;
	i = 0;
	while (av[i])
		ft_lstadd_back_env(&head, ft_lstnew_env(av[i++]));
	tmp = head;
	while (tmp)
	{
		if (ft_strcmp(tmp->env, "OLDPWD") == 0)
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = NULL;
		}
		tmp = tmp->next;
	}
	return (head);
}

void	ft_lstadd_back_env(t_envs **lst, t_envs *new)
{
	t_envs	*ptr;

	if (!lst)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	ptr = *lst;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

t_envs	*ft_lstnew_plus(char *str)
{
	t_envs	*new;

	new = my_malloc(sizeof(t_envs));
	if (!new)
		return (NULL);
	new->env = get_env_plus(str);
	new->value = get_value(str);
	new->next = NULL;
	return (new);
}

t_envs	*ft_lstnew_env(char *str)
{
	t_envs	*new;

	new = my_malloc(sizeof(t_envs));
	if (!new)
		return (NULL);
	new->env = get_envs(str);
	new->value = get_value(str);
	new->next = NULL;
	return (new);
}

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
