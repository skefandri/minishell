/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 12:12:07 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/06 12:12:09 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	handle_command_execution(t_data *data)
{
	if (!here_document(data))
		execution(data);
	else
		g_lob.exit_status = 1;
}

void	hadnle_signle(int n)
{
	(void) n;
	write(1, "\n", 1);
	rl_replace_line ("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_lob.exit_status = 1;
}

void	init_globals(char **env)
{
	g_lob.envs = set_envs(env);
	g_lob.exit_save = 0;
	g_lob.exit_status = 0;
}

void	process_input_line(char **line)
{
	g_lob.exit_save = g_lob.exit_status;
	*line = readline("minishell> ");
}
