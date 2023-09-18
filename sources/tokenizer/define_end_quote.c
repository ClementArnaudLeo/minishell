/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_end_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:38:38 by carnaud           #+#    #+#             */
/*   Updated: 2023/08/23 21:33:14 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	define_end_quote(char *token, bool has_variable,
			char first_quote, int *end_quote)
{
	char	*quote;

	quote = NULL;
	quote = ft_strchr(token, '\"');
	if (!quote && !has_variable)
		quote = ft_strchr(token, '\'');
	else if (quote && first_quote != '\'')
	{
		*quote = '\0';
		*end_quote = ft_strlen(token);
		*quote = '\"';
	}
	else if (!quote || first_quote == '\'')
		*end_quote = ft_strlen(token);
	else
	{
		*quote = '\0';
		*end_quote = ft_strlen(token);
		*quote = '\'';
	}
}
