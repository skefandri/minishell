/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 14:11:56 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/06 12:08:55 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	is_valid_start(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

char	*get_envs(char *str)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	s = my_malloc (i + 1);
	if (!s)
		return (NULL);
	while (j < i)
	{
		s[j] = str[j];
		j++;
	}
	s[j] = '\0';
	return (s);
}
