/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 00:51:50 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/13 09:20:38 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ve_andel(t_envp **envp, t_envp **prev, t_envp **current)
{
	if (!prev)
		*envp = (*current)->next;
	else
		(*prev)->next = (*current)->next;
	free((*current)->env->key);
	free((*current)->env->val);
	free((*current)->env);
	free(*current);
}

void	ve_andel0(t_struct **rr, t_envp **current)
{
	char	*temp;
	size_t	len;

	temp = ft_strdup((*current)->env->val);
	free((*current)->env->val);
	len = ft_strlen(temp) + ft_strlen((*rr)->val) + 1;
	(*current)->env->val = malloc(sizeof(char) * (len));
	if (!(*current)->env->val)
		exit(EXIT_FAILURE);
	(*current)->env->val[0] = '\0';
	ft_strcat((*current)->env->val, temp);
	ft_strcat((*current)->env->val, (*rr)->val);
	free(temp);
}

int	verife_env_and_del(t_envp **envp, t_struct **rr)
{
	t_envp	*cur;
	t_envp	*prev;
	int		i;

	cur = *envp;
	prev = NULL;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->env->key, (*rr)->key, ft_strlen((*rr)->key)) == 0
			&& ft_strncmp((*rr)->key, cur->env->key,
				ft_strlen(cur->env->key)) == 0)
		{
			i = andel(envp, &prev, &cur, rr);
			if (i == 1)
				return (1);
			else if (i == 0)
				return (0);
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}

void	re_set_enve(t_envp **envp, t_struct **rr)
{
	int		i;
	size_t	size;
	t_envp	*current;

	i = 0;
	while ((*rr)->enve[i])
		free((*rr)->enve[i++]);
	i = 0;
	size = 0;
	current = *envp;
	while (current != NULL)
	{
		size = ft_strlen(current->env->key) + ft_strlen(current->env->val) + 2;
		(*rr)->enve[i] = malloc(sizeof(char) * (size));
		if (!(*rr)->enve[i])
			return ;
		(*rr)->enve[i][0] = '\0';
		ft_strcat((*rr)->enve[i], current->env->key);
		ft_strcat((*rr)->enve[i], "=");
		ft_strcat((*rr)->enve[i], current->env->val);
		current = current->next;
		i++;
	}
	(*rr)->enve[i] = NULL;
}
