/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:53:42 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/05 10:28:26 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_value(char **env, char *temp, int start, int i)
{
	char	*value;
	int		j;

	value = NULL;
	j = 0;
	while (env[j])
	{
		if (ft_strncmp(temp, env[j], i - start) == 0
			&& env[j][i - start] == '=')
		{
			if (temp[i - start] != '\0'
				&& is_variable_character(temp[i - start]))
			{
				j++;
				continue ;
			}
			value = env[j] + i - start + 1;
			break ;
		}
		j++;
	}
	return (value);
}

char	*append_segment(char *result, char *str, int start, int end)
{
	char	*temp;
	char	*oldresult;

	temp = extract_substring(str, start, end);
	oldresult = result;
	if (result != NULL)
	{
		result = append_to_str(oldresult, temp);
		free(temp);
	}
	else
		result = temp;
	free(oldresult);
	return (result);
}

char	*append_env_value(char *result, char *value)
{
	char	*oldresult;

	if (result != NULL)
	{
		oldresult = result;
		result = append_to_str(oldresult, value);
		free(oldresult);
	}
	else
		result = str_alloc_copy(value);
	return (result);
}

int	ft_lstsize_envsss(t_envs *lst)
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

char	**lst_to_envs(t_envs *ptr)
{
	int		i;
	int		size;
	char	**args;
	char	*tmp;

	i = 0;
	size = ft_lstsize_envsss(ptr);
	args = my_malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		if (ptr->value)
		{
			args[i] = ft_strjoin(ptr->env, "=");
			tmp = args[i];
			args[i] = ft_strjoin(args[i], ptr->value);
			free(tmp);
		}
		else
			args[i] = ft_strdup(ptr->env);
		ptr = ptr->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}
