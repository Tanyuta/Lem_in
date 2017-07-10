/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 22:06:07 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/07/06 20:49:18 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	distribution_of_ants_3(t_node *st1, t_node *st2)
{
	if (st1->ant == 0 && st2->ant == 1 && st1->st_en != 'e')
	{
		st1->ant = 1;
		st2->ant = 0;
		st1->nbr = st2->nbr;
		st2->nbr = 0;
		write(1, "L", 1);
		ft_putnbr(st1->nbr);
		write(1, "-", 1);
		write(1, st1->name, ft_strlen(st1->name));
		write(1, " ", 1);
	}
	else if (st2->ant == 1 && st1->st_en == 'e')
	{
		st1->ant++;
		st2->ant = 0;
		st1->nbr = st2->nbr;
		st2->nbr = 0;
		write(1, "L", 1);
		ft_putnbr(st1->nbr);
		write(1, "-", 1);
		write(1, st1->name, ft_strlen(st1->name));
		write(1, " ", 1);
	}
}

void	distribution_of_ants_2(t_lemin *lemin, t_node *st1,
								t_node *st2, int i[2])
{
	if (i[1] != 2 && st1 && st2)
		distribution_of_ants_3(st1, st2);
	else if (st1 && i[1] == 2 && lemin->ways[i[0]][1] > 0 && st1->st_en != 's')
	{
		st1->ant = (st1->st_en == 'e') ? st1->ant + 1 : 1;
		lemin->ways[i[0]][1]--;
		st1->nbr = ++lemin->a;
		write(1, "L", 1);
		ft_putnbr(st1->nbr);
		write(1, "-", 1);
		write(1, st1->name, ft_strlen(st1->name));
		write(1, " ", 1);
	}
}

void	distribution_of_ants(t_lemin *lemin, int n)
{
	int		i[2];
	t_node	*st1;
	t_node	*st2;

	i[0] = -1;
	while (++i[0] < n)
	{
		i[1] = lemin->ways[i[0]][0] + 2;
		while (--i[1] > 1)
		{
			st1 = search_node(lemin, lemin->ways[i[0]][i[1]]);
			st2 = search_node(lemin, lemin->ways[i[0]][i[1] - 1]);
			distribution_of_ants_2(lemin, st1, st2, i);
		}
	}
	write(1, "\n", 1);
}

int		run_ants(t_lemin *lemin, int n)
{
	int		all;
	t_node	*st;

	all = 0;
	while (lemin->all_ants != all)
	{
		distribution_of_ants(lemin, n);
		st = search_node(lemin, lemin->lst_len - 1);
		all = st->ant;
	}
	return (0);
}

int		count_ants_for_ways(t_lemin *lemin)
{
	int		n_a[2];
	int		i;
	int		min;

	n_a[1] = lemin->all_ants;
	n_a[0] = ft_count_roads(lemin);
	while (n_a[1])
	{
		i = 0;
		min = lemin->ways[0][0] + lemin->ways[0][1];
		while (++i < n_a[0])
			if ((lemin->ways[i][0] + lemin->ways[i][1]) < min)
				min = lemin->ways[i][0] + lemin->ways[i][1];
		i = -1;
		while (++i < n_a[0])
			if ((lemin->ways[i][0] + lemin->ways[i][1]) == min)
			{
				lemin->ways[i][1]++;
				n_a[1]--;
				if (n_a[1] == 0)
					break ;
			}
	}
	print_map(lemin);
	return (run_ants(lemin, n_a[0]));
}
