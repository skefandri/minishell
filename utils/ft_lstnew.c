/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:07:11 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/01 18:03:05 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command	*ft_lstnew(void *content)
{
	t_command	*new;

	new = my_malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
