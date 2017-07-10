/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map_and_all_free.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 22:05:59 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/07/06 19:16:45 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_map(t_lemin *lemin)
{
	t_read	*st;

	st = lemin->lst;
	while (st)
	{
		write(1, st->str, ft_strlen(st->str));
		write(1, "\n", 1);
		st = st->next;
	}
	write(1, "\n", 1);
}

void	free_read(t_read *read)
{
	t_read	*tmp;

	while (read)
	{
		tmp = read;
		read = read->next;
		if (tmp->str)
			free(tmp->str);
		free(tmp);
	}
}

void	free_node(t_node *node)
{
	t_node	*tmp;

	while (node)
	{
		tmp = node;
		node = node->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp->link)
			free(tmp->link);
		free(tmp);
	}
}

void	free_lemin(t_lemin *lemin)
{
	int		i;

	free_read(lemin->lst);
	free_node(lemin->start);
	if (lemin->matrix)
	{
		i = -1;
		while (++i < lemin->lst_len)
			free(lemin->matrix[i]);
		free(lemin->matrix);
	}
	if (lemin->ways)
	{
		i = -1;
		while (++i < lemin->roads)
			free(lemin->ways[i]);
		free(lemin->ways);
	}
}

int		ft_count_roads(t_lemin *lemin)
{
	int		i;
	int		n;

	i = -1;
	n = 0;
	while (++i < lemin->roads)
	{
		if (lemin->ways[i] && lemin->ways[i][0] > 0)
			n++;
		else
			break ;
	}
	if (n == 0)
	{
		free_lemin(lemin);
		exit(write(2, "ERROR! No roads!\n", 17));
	}
	return (n);
}
