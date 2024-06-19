/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_main2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:09:32 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/13 09:14:50 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	cleanup_search_structures(char **arg, char **dir)
{
	free_tab((void **)arg);
	free_tab((void **)dir);
}

int	command_exist(char *cmd, t_struct **rr)
{
	char	*path;
	char	**dir;
	char	**arg;
	int		exist;

	path = NULL;
	if (!init_command_search(cmd, rr, &path))
		return (0);
	dir = NULL;
	arg = NULL;
	if (!setup_search_structures(path, cmd, &dir, &arg))
		return (0);
	exist = process_command_search(dir, arg, rr);
	cleanup_search_structures(arg, dir);
	return (exist);
}

void	destroy_file(void)
{
	int	status;

	if (access(".temp.txt", F_OK) == 0)
	{
		status = unlink(".temp.txt");
		if (status == 0)
			;
		else
			perror("Erreur de suppression de fichier");
	}
}
