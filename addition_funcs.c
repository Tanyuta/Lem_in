/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 22:04:09 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/07/06 19:28:45 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	check_x_y(t_lemin *lemin, t_node *node)
{
	t_node *st;

	st = lemin->node;
	while (st && st != node)
	{
		if (st->x == node->x && st->y == node->y)
		{
			free_lemin(lemin);
			exit(write(2, "ERROR! Dublicate coordinates!\n", 30));
		}
		st = st->next;
	}
}

int		max_roads(t_lemin *lemin)
{
	int		x;
	int		y;
	int		i;
	t_node	*st;

	st = lemin->node;
	x = 0;
	y = 0;
	i = -1;
	while (st && st->link && st->link[++i])
		x++;
	st = search_node(lemin, lemin->lst_len - 1);
	i = -1;
	while (st && st->link && st->link[++i])
		y++;
	x = (x > y) ? y : x;
	if (x == 0)
	{
		free_lemin(lemin);
		exit(write(2, "ERROR! No links with Start or End!\n", 35));
	}
	return (x);
}

int		count_words(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str && str[++i])
	{
		while (ISSPACE(str[i]))
			i++;
		if (str[i] && !(ISSPACE(str[i])))
		{
			count++;
			while (str[i] && !(ISSPACE(str[i])))
				i++;
		}
		if (!str[i])
			break ;
		i--;
	}
	return (count);
}

void	str_reverse(int *way, int len)
{
	int	i;
	int	j;
	int	t;

	i = 2;
	j = len - 1;
	while (i <= j)
	{
		t = way[i];
		way[i] = way[j];
		way[j] = t;
		i++;
		j--;
	}
}

int		length_name(char *str)
{
	int	len;

	len = 0;
	while (!(ISSPACE(*str)) && ft_isascii(*str))
	{
		len++;
		str++;
	}
	return (len);
}
