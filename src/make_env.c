/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:22:00 by wkeiser           #+#    #+#             */
/*   Updated: 2024/06/13 10:10:39 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	env_env(t_struct **rr)
{
	while ((*rr)->envv[(*rr)->i][(*rr)->f] != '=')
	{
		(*rr)->f++;
		(*rr)->l++;
	}
	(*rr)->f++;
	while ((*rr)->envv[(*rr)->i][(*rr)->f])
	{
		(*rr)->f++;
		(*rr)->g++;
	}
}

static char	*env_clean0(char ***tab)
{
	char	*pwd;
	char	cwd[1024];

	*tab = malloc(sizeof(char *) * 6);
	if (!*tab)
		return (NULL);
	pwd = getenv("PWD");
	if (!pwd)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			pwd = strdup(cwd);
		else
			pwd = strdup("/");
	}
	else
		pwd = strdup(pwd);
	return (pwd);
}

static char	*env_clean1(char *pwd)
{
	char	*pwd_str;

	pwd_str = malloc(strlen("PWD=") + strlen(pwd) + 1);
	if (!pwd_str)
	{
		free(pwd);
		return (NULL);
	}
	ft_strcpy(pwd_str, "PWD=");
	ft_strcat(pwd_str, pwd);
	free(pwd);
	return (pwd_str);
}

static void	env_0clean(char ***tab, t_struct **rr)
{
	int		id;
	char	*pwd;
	char	*pwd_str;

	id = 0;
	pwd = env_clean0(tab);
	pwd_str = env_clean1(pwd);
	if (!pwd_str)
	{
		free(*tab);
		return ;
	}
	(*tab)[id++] = pwd_str;
	(*tab)[id++] = ft_strdup("SHLVL=2");
	(*tab)[id++] = ft_strdup("_=/usr/bin/env");
	(*tab)[id++] = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:"
			"/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:"
			"/usr/local/games:/snap/bin:/snap/bin");
	(*tab)[id] = NULL;
	(*rr)->envv = *tab;
}

void	make_env(t_envp **envp, char **env, t_struct **rr)
{
	char	**tab;

	tab = NULL;
	if (!*env)
		env_0clean(&tab, rr);
	else
		(*rr)->envv = env;
	(*rr)->i = 0;
	(*rr)->f = 0;
	(*rr)->l = 0;
	(*rr)->g = 0;
	while ((*rr)->envv[(*rr)->i])
		refact_env(envp, rr);
	if (!*env)
		free_tab((void **)tab);
}
