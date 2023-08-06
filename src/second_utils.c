/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:55:05 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/03 18:41:04 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*remove_quotes(char *line)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	c = 0;
	while (line[i])
	{
		if (c == 0 && (line[i] == '\'' || line[i] == '\"'))
			c = line[i];
		else if (c == line[i])
			c = 0;
		else
			line[j++] = line[i];
		i++;
	}
	line[j] = '\0';
	return (line);
}

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

void	free_cmd(t_cmd *head)
{
	if (head != NULL)
	{
		free_cmd(head->next);
		free(head->cmd);
		free(head);
	}
}

void	free_file(t_file *head)
{
	if (head != NULL)
	{
		free_file(head->next);
		free(head->filename);
		if (head->type == 4 && head->fd > 2)
			close(head->fd);
		free(head);
	}
}

void	free_data(t_data *head)
{
	if (head != NULL)
	{
		free_data(head->next);
		free_file(head->file);
		free_cmd(head->cmd);
		free(head);
	}
}
