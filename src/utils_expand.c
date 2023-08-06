/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:09:34 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/02 18:52:42 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	str_len(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*str_alloc_copy(const char *src)
{
	int		len;
	char	*dest;
	int		i;

	len = str_len(src);
	i = 0;
	dest = (char *) my_malloc(len + 1);
	if (!dest)
		return (NULL);
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[len] = '\0';
	return (dest);
}

char	*append_to_str(char *dest, char *src)
{
	int		dest_len;
	int		src_len;
	char	*new_str;
	int		i;

	dest_len = str_len(dest);
	src_len = str_len(src);
	new_str = (char *)my_malloc(dest_len + src_len + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < dest_len)
	{
		new_str[i] = dest[i];
		i++;
	}
	i = 0;
	while (i < src_len)
	{
		new_str[dest_len + i] = src[i];
		i++;
	}
	new_str[dest_len + src_len] = '\0';
	return (new_str);
}

bool	is_variable_character(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

char	*extract_substring(char *str, int start, int end)
{
	char	*temp;
	int		j;

	j = start;
	temp = (char *)my_malloc(end - start + 1);
	if (!temp)
		return (NULL);
	while (j < end)
	{
		temp[j - start] = str[j];
		j++;
	}
	temp[end - start] = '\0';
	return (temp);
}
