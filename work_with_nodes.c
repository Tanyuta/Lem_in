/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_nodes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 22:06:16 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/07/05 22:06:18 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	create_node(t_node **node)
{
	*node = (t_node *)malloc(sizeof(t_node));
	**(node) = (t_node){ 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL};
}

t_node	*search_node(t_lemin *lemin, int n)
{
	t_node	*st;

	st = lemin->node;
	while (st)
	{
		if (st->index == n)
			return (st);
		st = st->next;
	}
	return (0);
}

void	depth_zero(t_lemin *lemin)
{
	t_node	*st;

	st = lemin->node;
	while (st)
	{
		st->depth = 0;
		st = st->next;
	}
}

void	index_list(t_node *st)
{
	int		i;

	i = -1;
	while (st)
	{
		st->index = ++i;
		st = st->next;
	}
}

int		list_size(t_node *list)
{
	int		count;

	count = 0;
	while (list)
	{
		list = list->next;
		count++;
	}
	return (count);
}
