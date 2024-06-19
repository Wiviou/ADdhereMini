/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_shell3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 01:27:45 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/13 09:04:53 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	read_fd0(char **command, t_struct **rr)
{
	if (access(command[0], F_OK) < 0)
		(*rr)->state.fd_fd = open(command[0], O_CREAT | O_TRUNC | O_RDWR, 0644);
	else
		(*rr)->state.fd_fd = open(command[0], O_WRONLY | O_APPEND, 0644);
	if ((*rr)->state.fd_fd == -1)
	{
		perror("Erreur lors de l'ouverture du fichier destination");
		close((*rr)->state.in_fd);
		return (0);
	}
	ft_get_endline((*rr)->state.in_fd, (*rr)->state.fd_fd);
	(*rr)->state.is_append = 0;
	return (1);
}

int	read_fd00(char **command, t_struct **rr)
{
	(*rr)->state.in_fd = open((*rr)->state.kkk, O_RDONLY);
	if ((*rr)->state.in_fd == -1)
	{
		perror("Erreur lors de l'ouverture du fichier source");
		free_tab((void **)command);
		return (0);
	}
	if ((*rr)->state.is_append)
	{
		if (!read_fd0(command, rr))
			return (0);
	}
	else
	{
		(*rr)->state.fd_fd = open(command[0], O_CREAT | O_TRUNC | O_RDWR, 0644);
		if ((*rr)->state.fd_fd == -1)
		{
			perror("Erreur lors de l'ouverture du fichier destination");
			close((*rr)->state.in_fd);
			return (0);
		}
		ft_get_line((*rr)->state.in_fd, (*rr)->state.fd_fd);
	}
	return (1);
}

static void	close_the_door_for_25_lines(t_struct **rr)
{
	close((*rr)->state.in_fd);
	close((*rr)->state.fd_fd);
}

int	read_fd1(char **command, t_struct **rr, t_node **node)
{
	close((*rr)->state.in_fd);
	(*rr)->state.in_fd = open((*rr)->state.kkk, O_TRUNC | O_RDWR);
	if ((*rr)->state.in_fd == -1)
	{
		perror("Erreur de la réouverture du fichier source pour troncature");
		close((*rr)->state.fd_fd);
		free_tab((void **)command);
		return (0);
	}
	close_the_door_for_25_lines(rr);
	if ((*rr)->state.kkk != NULL)
	{
		free((*rr)->state.kkk);
		(*rr)->state.kkk = NULL;
	}
	if ((*node)->next)
		if (ft_strncmp((*node)->next->sub->dta->val, ">", 1) == 0)
			(*rr)->state.kkk = ft_strdup(command[0]);
	(*rr)->state.k = 0;
	if ((*node)->next != NULL && ft_strncmp((*node)->next->sub->dta->val, ">",
			1) != 0)
		(*rr)->state.kj = 0;
	free_tab((void **)command);
	delete_node(node);
	return (1);
}
