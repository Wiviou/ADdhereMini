/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:34:13 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/17 22:12:10 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	pwd_fit(t_struct **rr, char *pwd)
{
	destroy_file();
	(*rr)->fd = open(".tmp.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if ((*rr)->fd != -1)
	{
		ft_putstr_fd(pwd, (*rr)->fd);
		ft_putchar_fd('\n', (*rr)->fd);
		close((*rr)->fd);
	}
	ft_get_line((*rr)->fd, 1);
	(*rr)->state.in_fd = open(".temp.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if ((*rr)->state.in_fd != -1)
	{
		ft_putstr_fd(pwd, (*rr)->state.in_fd);
		ft_putchar_fd('\n', (*rr)->state.in_fd);
		close((*rr)->state.in_fd);
	}
	ft_get_line((*rr)->fd, 1);
	(*rr)->state.is_in_echo = 0;
}

void	pwd_o(t_struct **rr)
{
	char	*pwd;
	char	cwd[1024];
	int		i;

	pwd = get_env("PWD", rr);
	if (!pwd || pwd[0] == '\0' || !*pwd )
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			pwd = ft_strdup(cwd);
		else
			pwd = ft_strdup("Inconnu");
		i = 0;
		while ((*rr)->enve[i])
			i++;
		printf("%s\n", pwd);
		free(pwd);
	}
	else
		printf("%s\n", pwd);
}

void	invite_pwd0(char *pwd, t_struct **rr)
{
	(*rr)->couleur_in = "\033[1;32m";
	(*rr)->couleur_out = "\033[0m\33[0;31m> \033[0m";
	(*rr)->len_invite = ft_strlen(pwd) + ft_strlen((*rr)->couleur_in)
		+ ft_strlen((*rr)->couleur_out) + 1;
	(*rr)->invite = malloc((*rr)->len_invite);
	if (!(*rr)->invite)
	{
		free(pwd);
		return ;
	}
	ft_strcpy((*rr)->invite, (*rr)->couleur_in);
	ft_strcat((*rr)->invite, pwd);
	ft_strcat((*rr)->invite, (*rr)->couleur_out);
	if (pwd != get_env("PWD", rr))
		free(pwd);
}

char	*invite_pwd(t_struct **rr)
{
	char	*pwd;
	char	cwd[1024];

	pwd = get_env("PWD", rr);
	if (!pwd)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			pwd = ft_strdup(cwd);
		else
			pwd = "Inconnu";
	}
	invite_pwd0(pwd, rr);
	return ((*rr)->invite);
}
