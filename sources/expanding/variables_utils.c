/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 22:00:35 by carnaud           #+#    #+#             */
/*   Updated: 2023/08/23 21:48:57 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_by_two(const char *string, char c)
{
	char	**splited_strings;
	char	*c_ptr;

	splited_strings = (char **)malloc(3 * sizeof(char *));
	c_ptr = ft_strchr(string, c);
	splited_strings[0] = ft_substr(string, 0, (c_ptr - string));
	splited_strings[1] = ft_substr((c_ptr + 1), 0, ft_strlen(c_ptr));
	splited_strings[2] = NULL;
	return (splited_strings);
}

char	**split_by_two_ptr(const char *string, char *c_ptr)
{
	char	**splited_strings;

	splited_strings = (char **)malloc(3 * sizeof(char *));
	splited_strings[0] = ft_substr(string, 0, (c_ptr - string));
	splited_strings[1] = ft_substr((c_ptr + 1), 0, ft_strlen(c_ptr));
	splited_strings[2] = NULL;
	return (splited_strings);
}

char	*search_var(char *value, int *i)
{
	while (value[*i] != '\0')
	{
		if (value[*i] == '$')
			return (&value[*i]);
		*i += 1;
	}
	return (NULL);
}

int	get_var_size(char *var, int *index)
{
	int	i;

	i = 0;
	while ((var[i + 1] != ' ') && (var[i + 1] != '\0') && (var[i + 1] != '$'))
		i++;
	i++;
	*index += i;
	return (i);
}

void	free_var_struct(t_var *var)
{
	ft_free_and_null((void **)&var->before);
	ft_free_and_null((void **)&var->value);
	ft_free_and_null((void **)&var->after);
}
