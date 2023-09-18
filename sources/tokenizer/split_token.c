/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 16:41:56 by carnaud           #+#    #+#             */
/*   Updated: 2023/08/18 03:45:28 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_end(char *line, int i, int *end)
{
	while (!(ft_isblank(line[i])) && (line[i]))
	{
		if (is_between_quotes(line, i, &i, line[i]))
		{
			i++;
			continue ;
		}
		i++;
	}
	*end = i;
	return (i);
}

int	split_token(char *line, int *i, int *tkn_end, t_token **token_lst)
{
	while (ft_isblank(line[*i]))
		*i += 1;
	if (!line[*i])
		return (0);
	add_token(line, *i, find_end(line, *i, tkn_end), token_lst);
	*i = *tkn_end;
	if (line[*i])
		*i += 1;
	return (1);
}
