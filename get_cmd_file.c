/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 12:10:59 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/06 12:11:01 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	handle_type_4(t_context *context, int count)
{
	char	*expand;

	expand = ft_strdup(context->lexer->next->content->content);
	ft_lstadd_back_file(&context->file,
		ft_lstnew_file(expand, context->lexer->content->e_type));
	return (count + 1);
}

void	handle_other_types(t_context *context)
{
	char	*expand;

	expand = expand_result(context->lexer->next->content->content,
			context->env, 0);
	ft_lstadd_back_file(&context->file,
		ft_lstnew_file(expand, context->lexer->content->e_type));
}

void	handle_type_3(t_context *context)
{
	char		*expand;
	t_command	*llexer;
	t_command	*tmp;

	llexer = NULL;
	expand = expand_result(context->lexer->content->content, context->env, 0);
	process_tokens(expand, &llexer);
	while (llexer && llexer->next)
	{
		tmp = llexer;
		ft_lstadd_back_cmd(&context->cmd,
			ft_lstnew_cmd(remove_quotes(llexer->content->content)));
		llexer = llexer->next;
	}
}

void	handle_type_0_6(t_context *context, t_data **data)
{
	if (context->lexer->content->e_type == 0
		|| context->lexer->content->e_type == 6)
	{
		ft_lstadd_back_data(data, ft_lstnew_data(context->file, context->cmd));
		g_lob.exit_status = 0;
		context->file = NULL;
		context->cmd = NULL;
	}
}
