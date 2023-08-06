/* ************************************************************************** */
/*			                                                                */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:08:41 by ysabr             #+#    #+#             */
/*   Updated: 2023/07/28 21:28:03 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_quotes(char *str, int *i, bool *in_s_quote, bool *in_d_quote)
{
	if (str[*i] == '\'')
	{
		if (!(*in_d_quote))
			*in_s_quote = !(*in_s_quote);
		(*i)++;
	}
	else if (str[*i] == '\"')
	{
		if (!(*in_s_quote))
			*in_d_quote = !(*in_d_quote);
		(*i)++;
	}
}

int	for_norm(t_sv *a, char c, char *str)
{
	int	r;

	r = 0;
	if (c == '?')
	{
		_exitstatus(a, str);
		r = 1;
	}
	else if (c == '$')
	{
		_dollarsign(a, str);
		r = 1;
	}
	else if ((c >= 48 && c <= 57) || c == '@' || c == '*')
	{
		special_chars(a, str);
		r = 1;
	}
	else if ((c == '\'') || (c == '"'))
	{
		qoutescase(a, str);
		r = 1;
	}
	return (r);
}

void	for_norm2(t_sv *a, char **env, char *str)
{
	char	*temp;
	char	*value;
	int		var_start;

	var_start = a->i + 1;
	while (str[var_start] != '\0' && is_variable_character(str[var_start]))
		var_start++;
	if (var_start != a->i + 1)
	{
		temp = extract_substring(str, a->i + 1, var_start);
		value = get_env_value(env, temp, a->i + 1, var_start);
		a->result = append_segment(a->result, str, a->start, a->i);
		if (value != NULL)
			a->result = append_env_value(a->result, value);
		free(temp);
		a->start = var_start;
	}
	else
	{
		a->result = append_segment(a->result, str, a->start, a->i + 1);
		a->start = a->i + 1;
	}
	a->i = var_start;
}

char	*expand_result(char *str, char **env, int hide)
{
	t_sv	a;

	init_vals(&a);
	while (str[a.i] != '\0')
	{
		if (str[a.i] == '\'' || str[a.i] == '\"')
		{
			handle_quotes(str, &a.i, &a.in_single_quotes, &a.in_double_quotes);
			continue ;
		}
		if (str[a.i] == '$' && (!a.in_single_quotes || hide))
		{
			if (for_norm(&a, str[a.i + 1], str))
				continue ;
			for_norm2(&a, env, str);
		}
		else
			a.i++;
	}
	a.result = append_segment(a.result, str, a.start, a.i);
	return (a.result);
}
