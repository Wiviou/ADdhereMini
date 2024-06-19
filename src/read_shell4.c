/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_shell4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 01:32:04 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/17 23:36:21 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	read_jkl(int *jkl, char **command, t_struct **rr)
{
	*jkl = 0;
	while (command[0][*jkl] == ' ' && command[0][*jkl])
		*jkl += 1;
	if (command[0][*jkl] == '\0')
		printf("minisihell: : No such file or directory\n");
	if (access(command[0], F_OK) < 0)
		(*rr)->state.fd_fd = open(command[0], O_CREAT | O_TRUNC | O_RDWR, 0644);
	else
		(*rr)->state.fd_fd = open(command[0], O_WRONLY | O_APPEND, 0644);
	ft_get_line((*rr)->state.in_fd, (*rr)->state.fd_fd);
	(*rr)->state.is_append = 0;
}

static void	read_jkl0(int *jkl, char **command, t_struct **rr)
{
	*jkl = 0;
	while (command[0][*jkl] == ' ' && command[0][*jkl])
		*jkl += 1;
	if (command[0][*jkl] == '\0')
		printf("minisihell: : No such file or directory\n");
	(*rr)->state.fd_fd = open(command[0], O_CREAT | O_TRUNC | O_RDWR, 0644);
	ft_get_line((*rr)->state.in_fd, (*rr)->state.fd_fd);
}

static void	read_jkl1(int *jkl, char **command, t_struct **rr, t_node **node)
{
	if ((*rr)->state.is_append)
		read_jkl(jkl, command, rr);
	else if ((*rr)->simple_file)
	{
		(*rr)->state.fd_fd = open(command[0], O_CREAT | O_TRUNC | O_RDWR, 0644);
		(*rr)->simple_file = 0;
	}
	else
		read_jkl0(jkl, command, rr);
	unlink(".temp.txt");
	close((*rr)->state.in_fd);
	close((*rr)->state.fd_fd);
	(*rr)->state.k = 0;
	if ((*node)->next != NULL && ft_strncmp((*node)->next->sub->dta->val, ">",
			1) != 0)
		(*rr)->state.kj = 0;
	free_tab((void **)command);
	delete_node(node);
}

void	read_jkll(int *jkl, t_struct **rr, t_node **node, char **command)
{
	if ((*rr)->state.kkk != NULL)
	{
		free((*rr)->state.kkk);
		(*rr)->state.kkk = NULL;
	}
	if ((*node)->next)
		if (ft_strncmp((*node)->next->sub->dta->val, ">", 1) == 0)
			(*rr)->state.kkk = ft_strdup(command[0]);
	(*rr)->state.in_fd = open(".temp.txt", O_RDONLY, 0644);
	read_jkl1(jkl, command, rr, node);
}

int	read_cd(char **command, t_struct **rr, t_node **node, t_envp **envp)
{
	if ((*rr)->nbr_pipe)
	{
		delete_node(node);
		free_tab((void **)command);
		return (7);
	}
	else
		cd_command(command, rr, envp);
	delete_node(node);
	free_tab((void **)command);
	return (7);
}
