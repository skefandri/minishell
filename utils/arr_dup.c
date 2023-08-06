/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 12:11:06 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/06 12:11:08 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**arr_dup(char **tab)
{
	char	**dup;
	int		i;

	dup = my_malloc(sizeof(char *) * (ft_tabsize(tab) + 1));
	if (!dup)
		exit(EXIT_FAILURE);
	i = 0;
	while (tab[i])
	{
		dup[i] = ft_strdup(tab[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
