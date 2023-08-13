/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 08:27:31 by ysabr             #+#    #+#             */
/*   Updated: 2023/07/27 10:07:18 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_pwd_old(t_envs	*envs, char *name, char *value)
{
	if (!name || !value)
		return ;
	while (envs)
	{
		if (ft_strcmp(envs->env, "PWD") == 0)
		{
			free(envs->value);
			envs->value = ft_strdup(name);
		}
		if (ft_strcmp(envs->env, "OLDPWD") == 0)
		{
			free(envs->value);
			envs->value = ft_strdup(value);
		}
		envs = envs->next;
	}
}

char	*my_getenv(const char *name)
{
	t_envs	*tmp;

	tmp = g_lob.envs;
	while (tmp)
	{
		if (ft_strcmp(tmp->env, name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	chdir_to(char *path)
{
	int	p;

	if (path == NULL)
	{
		printf("cd: path not set\n");
		return (-1);
	}
	p = chdir(path);
	if (p)
	{
		perror(path);
		g_lob.exit_status = 1;
	}
	return (p);
}

int	handle_cd_special_cases(char **args)
{
	int	result;

	result = -1;
	if (args[1] == NULL || ft_strcmp(args[1], "~") == 0)
		result = chdir_to(my_getenv("HOME"));
	else if (ft_strcmp(args[1], ".") == 0)
		result = 0;
	else if (ft_strcmp(args[1], "..") == 0)
		result = chdir_to("..");
	else if (ft_strcmp(args[1], "-") == 0)
		result = chdir_to(my_getenv("OLDPWD"));
	else if (ft_strcmp(args[1], "--") == 0)
	{
		if (args[2] == NULL)
			result = chdir(my_getenv("HOME"));
		else
			result = chdir(args[2]);
	}
	else
		result = chdir_to(args[1]);
	return (result);
}

int	cd_cmd(char **args)
{
	int		result;
	char	*original_dir;
	char	*new_dir;
	t_envs	*envs;

	envs = g_lob.envs;
	original_dir = getcwd(NULL, 0);
	result = handle_cd_special_cases(args);
	new_dir = getcwd(NULL, 0);
	if (new_dir == NULL && original_dir == NULL)
	{
		write(2, "cd: error retrieving current directory:", 40);
		write(2, " getcwd : cannot access parent directories: ", 45);
		write(2, "No such file or directory\n", 27);
		return (-1);
	}
	set_pwd_old(envs, new_dir, original_dir);
	free(original_dir);
	free(new_dir);
	return (result);
}
