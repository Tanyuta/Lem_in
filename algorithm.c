/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 22:04:54 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/07/06 19:34:51 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	initialize_way(t_lemin *lemin, int len, int *way)
{
	way[0] = len;
	way[1] = 0;
	way[2] = lemin->lst_len - 1;
}

void	write_road(t_lemin *lemin, int *way, int len)
{
	int		i_j_l[3];
	t_node	*st[2];

	i_j_l[0] = 2;
	i_j_l[2] = lemin->lst_len;
	initialize_way(lemin, len, way);
	while ((i_j_l[1] = -1) && --i_j_l[2] > 0)
		while (++i_j_l[1] < lemin->lst_len)
			if (lemin->matrix[i_j_l[2]][i_j_l[1]] == 1)
			{
				st[0] = search_node(lemin, i_j_l[2]);
				st[1] = search_node(lemin, i_j_l[1]);
				if (st[0] && st[1] && st[1]->depth == st[0]->depth - 1)
					if (len-- > 0)
					{
						if (st[1]->st_en == 's')
							continue;
						(st[0]->st_en != 'e') ? st[0]->flag = -1 : 0;
						(st[1]->st_en != 'e' && st[1]->st_en != 's') ?
												st[1]->flag = -1 : 0;
						way[++i_j_l[0]] = i_j_l[1];
						i_j_l[2] = i_j_l[1] + 1;
						break ;
					}
			}
}

int		write_depth(t_node *st, t_lemin *lemin, int d)
{
	int	i;

	i = -1;
	if (st->st_en == 'e')
	{
		st->depth = (st->depth == 0 || st->depth > d) ? d : st->depth;
		return (0);
	}
	while (st->link && st->link[++i])
	{
		if (st->link[i]->st_en == 's')
			continue ;
		if ((st->link[i]->depth == 0 || st->link[i]->depth > d + 1) &&
				st->link[i]->flag != -1)
			st->link[i]->depth = d + 1;
	}
	i = 0;
	while (st->link && st->link[i])
	{
		if ((st->link[i]->depth == 0 || st->link[i]->depth >= d + 1) &&
				st->link[i]->st_en != 's' && st->link[i]->flag != -1)
			write_depth(st->link[i], lemin, d + 1);
		i++;
	}
	return (0);
}

void	lemin_funcs(t_lemin *lemin)
{
	int		i;
	int		len;
	t_node	*st;
	t_node	*end;

	i = -1;
	lemin->roads = max_roads(lemin);
	lemin->ways = (int**)malloc(sizeof(int*) * lemin->roads);
	while (++i < lemin->roads)
		lemin->ways[i] = 0;
	i = -1;
	while (++i < lemin->roads)
	{
		st = lemin->node;
		depth_zero(lemin);
		write_depth(st, lemin, 0);
		end = search_node(lemin, lemin->lst_len - 1);
		len = (end->depth == 0) ? end->depth : end->depth + 2;
		lemin->ways[i] = (int *)malloc(sizeof(int) * len);
		ft_bzero(lemin->ways[i], len);
		write_road(lemin, lemin->ways[i], len - 2);
		str_reverse(lemin->ways[i], len);
		if ((len - 2) == 1)
			break ;
	}
}

void	write_matrix(t_lemin *lemin)
{
	int		i;
	int		j;
	t_node	*st;

	i = -1;
	st = lemin->node;
	index_list(st);
	lemin->matrix = (int**)malloc(sizeof(int*) * lemin->lst_len);
	while (++i < lemin->lst_len)
		lemin->matrix[i] = (int*)malloc(sizeof(int) * lemin->lst_len);
	i = -1;
	while ((j = -1) && ++i < lemin->lst_len)
		while (++j < lemin->lst_len)
			lemin->matrix[i][j] = 0;
	while (st)
	{
		i = -1;
		while (st->link && st->link[++i])
		{
			lemin->matrix[st->index][st->link[i]->index] = 1;
			lemin->matrix[st->link[i]->index][st->index] = 1;
		}
		st = st->next;
	}
}
