/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 12:10:49 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/12 08:11:47 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_vals(t_sv *a)
{
	a->i = 0;
	a->start = 0;
	a->result = NULL;
	a->in_single_quotes = false;
	a->in_double_quotes = false;
}

void	_exitstatus(t_sv *a, char *str)
{
	char	*exit_statusv;

	exit_statusv = ft_itoa(g_lob.exit_status);
	a->result = append_segment(a->result, str, a->start, a->i);
	a->result = append_to_str(a->result, exit_statusv);
	a->start = a->i + 2;
	a->i += 2;
}

void	_dollarsign(t_sv *a, char *str)
{
	a->result = append_segment(a->result, str, a->start, a->i + 1);
	a->start = a->i + 1;
	a->i += 2;
}

void	special_chars(t_sv *a, char *str)
{
	a->result = append_segment(a->result, str, a->start, a->i);
	a->start = a->i + 2;
	a->i += 2;
}

void	qoutescase(t_sv *a, char *str)
{
	a->result = append_segment(a->result, str, a->start, a->i);
	a->start = a->i;
	if (!a->in_double_quotes && !a->in_single_quotes)
		a->start++;
	a->i += 1;
}
