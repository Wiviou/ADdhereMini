/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liste_env2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 00:19:09 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/13 09:04:09 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_envp(t_envp *envp)
{
	
	while (envp != NULL)
	{
		
			printf("%s=%s", envp->env->key, envp->env->val);
			envp = envp->next;
			printf("\n");
	
	}
	
}

void	delete_envp(t_envp **head_ref)
{
	t_envp	*current;
	t_envp	*temp;

	if (head_ref == NULL || *head_ref == NULL)
	{
		return ;
	}
	current = *head_ref;
	while (current != NULL)
	{
		temp = current->next;
		if (current->env != NULL)
		{
			free(current->env->key);
			free(current->env->val);
			free(current->env);
		}
		free(current);
		current = temp;
	}
	*head_ref = NULL;
}

void	delete_env2(t_envp **head_ref, char *key_to_delete)
{
	size_t	t;
	t_envp	*current;
	t_envp	*before;

	t = ft_strlen(key_to_delete);
	current = *head_ref;
	before = NULL;
	while (current != NULL)
	{
		if (ft_strncmp(current->env->key, key_to_delete, t) == 0
			&& current->env->key[t] == '\0')
		{
			if (before == NULL)
				*head_ref = current->next;
			else
				before->next = current->next;
			free(current->env->key);
			free(current->env->val);
			free(current->env);
			free(current);
			break ;
		}
		before = current;
		current = current->next;
	}
}

void	delete_env(t_envp **head_ref, char **key, t_struct **rr)
{
	int	i;

	i = 1;
	while (key[i])
	{
		delete_env2(head_ref, key[i]);
		i++;
	}
	re_set_enve(head_ref, rr);
}
