/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:20:26 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/13 10:46:33 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*handle_elem(t_list **nl, void *nc, void (*del)(void *))
{
	t_list	*elem;

	elem = ft_lstnew(nc);
	if (!elem)
	{
		del(nc);
		ft_lstclear(nl, del);
		return (NULL);
	}
	ft_lstadd_back(nl, elem);
	return (elem);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	void	*new_cont;

	new_list = NULL;
	if (!lst || !f)
		return (NULL);
	while (lst)
	{
		new_cont = f(lst->content);
		if (!new_cont)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		if (!handle_elem(&new_list, new_cont, del))
			return (NULL);
		lst = lst->next;
	}
	return (new_list);
}
