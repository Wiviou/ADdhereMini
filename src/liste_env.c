/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liste_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkeiser <wkeiser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 00:19:09 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/11 09:43:06 by wkeiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_envp	*create_t_envp(char *key, char *val)
{
	t_envp	*new_envp;

	new_envp = malloc(sizeof(t_envp));
	if (!new_envp)
		return (NULL);
	new_envp->env = malloc(sizeof(t_env));
	if (!new_envp->env)
	{
		free(new_envp);
		return (NULL);
	}
	new_envp->env->val = val;
	new_envp->env->key = key;
	new_envp->next = NULL;
	return (new_envp);
}

void	push_env(t_envp **head_ref, char *key, char *val)
{
	t_envp	*new_envp;

	new_envp = create_t_envp(key, val);
	new_envp->next = *head_ref;
	*head_ref = new_envp;
}

void	append_envp(t_envp **head_ref, char *key, char *val)
{
	t_envp	*new_envp;
	t_envp	*last;

	new_envp = create_t_envp(key, val);
	if (*head_ref == NULL)
	{
		*head_ref = new_envp;
		return ;
	}
	last = *head_ref;
	while (last->next != NULL)
		last = last->next;
	last->next = new_envp;
}

int	stor_env2(t_envp *current, t_struct **rr, int *index)
{
	int		size;
	char	*env_str;

	size = strlen(current->env->key) + strlen(current->env->val) + 2;
	env_str = malloc(size);
	if (!env_str)
		return (0);
	env_str[0] = '\0';
	ft_strcat(env_str, current->env->key);
	ft_strcat(env_str, "=");
	ft_strcat(env_str, current->env->val);
	(*rr)->enve[*index] = env_str;
	(*index)++;
	return (1);
}

void	stor_env(t_envp **envp, t_struct **rr)
{
	int		i;
	t_envp	*current;

	i = 0;
	current = *envp;
	if (!(*rr)->enve)
		return ;
	while (current != NULL)
	{
		if (!current->env->key || !current->env->val)
		{
			current = current->next;
			continue ;
		}
		if (!stor_env2(current, rr, &i))
		{
			while (i > 0)
				free((*rr)->enve[--i]);
			return ;
		}
		current = current->next;
	}
	(*rr)->enve[i] = NULL;
}
