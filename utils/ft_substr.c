/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:46:56 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/04 10:47:46 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*ptr;

	if (!s)
		return (0);
	i = ft_strlen(s);
	if (len == 0 || start > i)
		return (ft_strdup(""));
	if (len > i - start)
		len = i - start;
	ptr = my_malloc ((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i] && (len > 0))
	{
		ptr[i] = s[i + start];
		i++;
		len--;
	}
	ptr[i] = '\0';
	return (ptr);
}
