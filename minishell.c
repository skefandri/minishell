/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   minishell.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ysabr <ysabr@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/05/19 11:17:37 by ysabr			 #+#	#+#			 */
/*   Updated: 2023/07/22 18:41:49 by ysabr			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "includes/minishell.h"

t_data	*handle_conditions(t_context *context, t_data *data, int *count)
{
	if (context->lexer->content->e_type != 0
		&& context->lexer->content->e_type != 3
		&& context->lexer->content->e_type != 6)
	{
		if (context->lexer->content->e_type == 4)
		{
			*count = handle_type_4(context, *count);
			if (*count > 16)
			{
				printf("minishell: maximum here-document count exceeded\n");
				exit (1);
			}
		}
		else
			handle_other_types(context);
		context->lexer = context->lexer->next;
	}
	else if (context->lexer->content->e_type == 3)
		handle_type_3(context);
	else
		handle_type_0_6(context, &data);
	context->lexer = context->lexer->next;
	return (data);
}

t_data	*get_cmd_file(t_context *context)
{
	int		count;
	t_data	*data;

	count = 0;
	data = NULL;
	if (!context->lexer || context->lexer->content->e_type == 6)
		return (NULL);
	while (context->lexer)
		data = handle_conditions(context, data, &count);
	return (data);
}

t_data	*process_commands(char *line, t_context *context)
{
	t_data	*data;

	data = NULL;
	process_tokens(line, &context->lexer);
	if (context->lexer && context->lexer->content->e_type != 6)
		add_history(line);
	if (!check_syntax_errors(context->lexer) && !check_quotes(line))
	{
		context->file = NULL;
		context->cmd = NULL;
		data = NULL;
		context->env = lst_to_envs(g_lob.envs);
		data = get_cmd_file(context);
	}
	return (data);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_context	context;
	t_data		*data;

	(void)av;
	if (ac != 1)
		return (1);
	init_globals(env);
	while (1)
	{
		signal (SIGINT, hadnle_signle);
		signal(SIGQUIT, SIG_IGN);
		process_input_line(&line);
		if (!line)
			return (g_lob.exit_status);
		signal(SIGINT, SIG_IGN);
		context.lexer = NULL;
		data = process_commands(line, &context);
		handle_command_execution(data);
		free(line);
		free_data(data);
	}
	return (0);
}
