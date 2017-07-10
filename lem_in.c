/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 22:05:35 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/07/07 18:23:00 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	check_map(t_lemin *lemin, t_read **st, int *flag)
{
	char	*cp;

	if ((*st)->next && ft_strcmp((*st)->str, "##start") == 0)
		((*st) = (*st)->next) && write_start_end((*st)->str, lemin, 1);
	else if ((*st)->next && ft_strcmp((*st)->str, "##end") == 0)
		((*st) = (*st)->next) && write_start_end((*st)->str, lemin, 0);
	else if (ft_strchr(((*st)->str + 1), '-'))
	{
		if (*flag == 0 && (*flag = 1))
			add_start_end(lemin);
		search_name_links_s1((*st)->str, lemin);
	}
	else
	{
		cp = (*st)->str;
		if (lemin->all_ants == 0)
			lemin->all_ants = lemin_atoi(&cp, lemin);
		else
		{
			free_lemin(lemin);
			exit(write(2, "ERROR map!\n", 11));
		}
	}
}

void	lemin_write(t_lemin *lemin)
{
	int		flag;
	t_read	*st;

	st = lemin->lst;
	flag = 0;
	while (st)
	{
		if (st->str && st->str[0] == '#' && ft_strcmp(st->str, "##start") &&
			ft_strcmp(st->str, "##end"))
		{
			st = st->next;
			continue;
		}
		if (count_words(st->str) == 1)
			check_map(lemin, &st, &flag);
		else if (count_words(st->str) == 3)
			write_coordinate(st->str, lemin);
		else
		{
			free_lemin(lemin);
			exit(write(2, "ERROR! Arguments are not valid!\n", 32));
		}
		st = st->next;
	}
}

t_read	*initializer(t_lemin *lemin, int flag)
{
	t_read	*st;

	if (flag == 1)
	{
		lemin->lst = (t_read*)malloc(sizeof(t_read));
		*(lemin->lst) = (t_read){NULL, NULL};
		st = lemin->lst;
		return (st);
	}
	else if (flag == 0)
	{
		free_lemin(lemin);
		exit(write(2, "ERROR! We don't have file whith map!\n", 37));
	}
	return (0);
}

void	lemin_read(t_lemin *lemin)
{
	char	*line;
	int		check;
	char	*tmp;
	t_read	*st;

	st = initializer(lemin, 1);
	while ((check = get_next_line(0, &line)) > 0)
	{
		tmp = line;
		line = ft_strtrim(line);
		if (st->str)
		{
			while (st->next)
				st = st->next;
			st->next = (t_read*)malloc(sizeof(t_read));
			st = st->next;
			*st = (t_read){NULL, NULL};
		}
		st->str = ft_strdup(line);
		free(line);
		free(tmp);
	}
	if (check < 0)
		initializer(lemin, 0);
	free(line);
}

int		main(void)
{
	t_lemin	lemin;

	lemin = (t_lemin){0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL};
	lemin_read(&lemin);
	lemin_write(&lemin);
	if (lemin.all_ants <= 0)
	{
		free_lemin(&lemin);
		exit(write(2, "ERROR! Don't valid ants!\n", 25));
	}
	write_matrix(&lemin);
	lemin_funcs(&lemin);
	count_ants_for_ways(&lemin);
	free_lemin(&lemin);
	return (0);
}
