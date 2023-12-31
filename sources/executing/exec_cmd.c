/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:30:15 by carnaud           #+#    #+#             */
/*   Updated: 2023/08/23 22:48:07 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	recup_path(char **path_variable, char **cmd)
{
	*path_variable = dico_search(g_minishell.env, "PATH");
	if (!*path_variable)
	{
		*path_variable = dico_search(g_minishell.local_vars, "PATH");
		if (!*path_variable)
		{
			err_msg(cmd[0], NO_FILE, 127);
			return (FALSE);
		}
	}
	return (TRUE);
}

static int	add_path_to_cmd_name(char **cmd)
{
	char	*cmd_name;
	char	*path_variable;

	if (!cmd[0] || (!recup_path(&path_variable, cmd)))
		return (0);
	cmd_name = get_absolute_path(cmd[0], path_variable);
	if (!cmd_name)
	{
		err_msg(cmd[0], NOT_FOUND, 127);
		return (0);
	}
	free(cmd[0]);
	cmd[0] = cmd_name;
	return (1);
}

static void	switch_builtin(char **cmd)
{
	if (!(ft_strcmp(cmd[0], "echo\0")))
		echo(cmd);
	else if (!(ft_strcmp(cmd[0], "cd\0")))
		cd(cmd[1]);
	else if (!(ft_strcmp(cmd[0], "pwd")))
		pwd();
	else if (!(ft_strcmp(cmd[0], "export")))
		export_(cmd);
	else if (!(ft_strcmp(cmd[0], "unset")))
		unset(cmd);
	else if (!(ft_strcmp(cmd[0], "env")))
		print_environment(g_minishell.env, STDOUT_FILENO);
	else if (!(ft_strcmp(cmd[0], "exit")))
		exit_builtin(cmd);
}

static void	execute_cmd(char **cmd)
{
	int		pid;
	int		status;
	char	**env_variables;

	if ((!cmd[0]) || (!add_path_to_cmd_name(cmd)))
		return ;
	pid = fork();
	define_signals2();
	if (pid == 0)
	{
		env_variables = dico_to_env(g_minishell.env);
		execve(cmd[0], cmd, env_variables);
		free_2d_array(env_variables);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_minishell.error_status = WEXITSTATUS(status);
}

void	execute(char **cmd)
{
	int	i;

	i = 0;
	if (cmd[i])
	{
		if (ft_strchr(cmd[i], '='))
			set_local_var(cmd, &i);
	}
	if (is_builtin(cmd[i]))
		switch_builtin(&cmd[i]);
	else
		execute_cmd(&cmd[i]);
}
