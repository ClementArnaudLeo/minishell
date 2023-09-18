/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 21:11:55 by carnaud           #+#    #+#             */
/*   Updated: 2023/08/23 21:33:14 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_quotes(char **value)
{
	int		i;
	int		end_quote;
	char	*token;

	i = 0;
	token = *value;
	while (token[i])
	{
		if (is_between_quotes(token, i, &end_quote, token[i]))
		{
			handle_quotes(&token, i, &end_quote);
			i = end_quote - 1;
			if (i < 0)
				i = 0;
		}
		if (token[i])
			i++;
	}
	*value = token;
}

void	add_token(char *line, int start, int end, t_token **token_lst)
{
	char	*value;
	int		type;

	value = ft_substr(line, start, (end - start));
	if (!value)
		return ;
	if (if_is_special_case(value))
		cas_speciaux(&value);
	else if (ft_strchr(value, '\'') || ft_strchr(value, '\"'))
		check_quotes(&value);
	else if (ft_strchr(value, '$'))
		expand_variables(&value);
	define_type(token_last(*token_lst), value, &type);
	token_add_back(token_lst, token_new(value, type));
}
