/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 02:21:11 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/10 11:55:16 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *cmd)
{
	int	i;

	if (!cmd)
		return (0);
	i = 0;
	if (!ft_strcmp(cmd, "echo"))
		i = 1;
	else if (!ft_strcmp(cmd, "env"))
		i = 2;
	else if (!ft_strcmp(cmd, "export"))
		i = 3;
	else if (!ft_strcmp(cmd, "unset"))
		i = 4;
	else if (!ft_strcmp(cmd, "cd"))
		i = 5;
	else if (!ft_strcmp(cmd, "pwd"))
		i = 6;
	else if (!ft_strcmp(cmd, "exit"))
		i = 7;
	return (i);
}

void	exec_builtin(char **args, int index)
{
	if (!args)
		error_check(1, NULL);
	else if (index == 1)
		simple_echo(args);
	else if (index == 2)
		_env(args);
	else if (index == 3)
		re_export(args + 1);
	else if (index == 4)
		re_unset(args + 1);
	else if (index == 5)
		cd_cmd(args);
	else if (index == 6)
		pwd(g_lob.envs);
	else if (index == 7)
		exit_cmd(args);
	return ;
}

int	ft_lstsize(t_cmd *lst)
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

char	**lst_to_args(t_cmd *ptr)
{
	int		i;
	int		size;
	char	**args;

	i = 0;
	size = ft_lstsize(ptr);
	args = my_malloc(sizeof(char *) * (size + 1));
	if (!args)
		return (NULL);
	if (!args)
	{
		perror("my_malloc");
		return (NULL);
	}
	while (i < size)
	{
		args[i] = ptr->cmd;
		ptr = ptr->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}
