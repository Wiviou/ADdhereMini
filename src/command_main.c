/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:25:28 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/13 09:02:24 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	set_cd(t_struct **rr, char *new_cd)
{
	int	i;

	i = 0;
	while ((*rr)->enve[i])
	{
		if (ft_strncmp((*rr)->enve[i], "PWD", 3) == 0)
		{
			free((*rr)->enve[i]);
			(*rr)->enve[i] = malloc(sizeof(char) * (ft_strlen(new_cd) + 5));
			if (!(*rr)->enve[i])
				return (0);
			ft_strcpy((*rr)->enve[i], "PWD=");
			ft_strcat((*rr)->enve[i], new_cd);
			return (1);
		}
		i++;
	}
	return (0);
}

void	re_envp(t_envp **envp, char *new_pwd)
{
	t_envp	*current;

	current = *envp;
	while (current != NULL)
	{
		if (ft_strncmp(current->env->key, "PWD", 3) == 0)
		{
			free(current->env->val);
			current->env->val = malloc(sizeof(char) * (ft_strlen(new_pwd) + 1));
			if (!current->env->val)
				return ;
			ft_strcpy(current->env->val, new_pwd);
		}
		current = current->next;
	}
	free(new_pwd);
}

static void	cd_command01(char *new_pwd, t_envp **envp, t_struct **rr)
{
	new_pwd = getcwd(NULL, 0);
	if (new_pwd != NULL)
	{
		if (!set_cd(rr, new_pwd))
		{
			push_env(envp, ft_strdup("PWD"), ft_strdup(new_pwd));
			re_set_enve(envp, rr);
		}
		re_envp(envp, ft_strdup(new_pwd));
		re_set_enve(envp, rr);
		free(new_pwd);
	}
	else
		perror("cd: getcwd failled");
}

int	cd_command(char **tab, t_struct **rr, t_envp **envp)
{
	char	*path;
	char	*new_pwd;

	path = NULL;
	if (ft_strncmp(tab[0], "cd", 2) == 0 && tab[0][2] == '\0')
	{
		destroy_file();
		if (tab[1] == NULL || (ft_strncmp(tab[1], "~", 1) == 0
				&& tab[1][1] == '\0'))
			path = getenv("HOME");
		else
			path = tab[1];
		if (chdir(path) == 0)
		{
			new_pwd = NULL;
			cd_command01(new_pwd, envp, rr);
		}
		else
			perror("cd: chdir failled");
		return (1);
	}
	return (0);
}
