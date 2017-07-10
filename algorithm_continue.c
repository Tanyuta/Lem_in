/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_continue.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 22:05:12 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/07/06 19:35:28 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	write_link_2(t_node *s1, t_node *s2, t_lemin *lemin)
{
	int		i;

	i = -1;
	while (++i < lemin->lst_len)
	{
		if (s1->link[i] == s2)
			break ;
		if (s1->link[i] == NULL)
		{
			s1->link[i] = s2;
			break ;
		}
	}
	i = -1;
	while (++i < lemin->lst_len)
	{
		if (s2->link[i] == s1)
			break ;
		if (s2->link[i] == NULL)
		{
			s2->link[i] = s1;
			break ;
		}
	}
}

void	write_link(t_node *s1, t_node *s2, t_lemin *lemin)
{
	int		i;
	t_node	*st;

	st = lemin->node;
	lemin->lst_len = list_size(st);
	if (!s1->link)
	{
		s1->link = (t_node **)malloc(sizeof(t_node *) * lemin->lst_len);
		i = -1;
		while (++i < lemin->lst_len)
			s1->link[i] = NULL;
	}
	if (!s2->link)
	{
		s2->link = (t_node **)malloc(sizeof(t_node *) * lemin->lst_len);
		i = -1;
		while (++i < lemin->lst_len)
			s2->link[i] = NULL;
	}
	write_link_2(s1, s2, lemin);
}

void	search_name_links_s2(char *str, t_lemin *lemin, t_node *s1)
{
	int		i;
	t_node	*st;

	st = lemin->node;
	while (st)
	{
		i = -1;
		while (st->name[++i])
			if (st->name[i] != str[i])
				break ;
		if (st->name[i] == '\0' && str[i] == '\0')
		{
			write_link(s1, st, lemin);
			break ;
		}
		st = st->next;
	}
	if (st == NULL)
	{
		free_lemin(lemin);
		exit(write(2, "ERROR! There isn't this name!\n", 30));
	}
}

void	search_name_links_s1(char *str, t_lemin *lemin)
{
	int		i;
	t_node	*st;

	st = lemin->node;
	while (st)
	{
		i = -1;
		while (st->name[++i])
			if (st->name[i] != str[i])
				break ;
		if (st->name[i] == '\0' && str[i] == '-')
		{
			search_name_links_s2((str + (++i)), lemin, st);
			break ;
		}
		st = st->next;
	}
	if (st == NULL)
	{
		free_lemin(lemin);
		exit(write(2, "ERROR! There isn't this name!\n", 30));
	}
}

void	add_start_end(t_lemin *lemin)
{
	t_node	*st;

	st = lemin->node;
	if (st && lemin->start && lemin->end)
	{
		lemin->start->next = lemin->node;
		lemin->node = lemin->start;
		while (st->next)
			st = st->next;
		st->next = lemin->end;
	}
	else if (!st && lemin->start && lemin->end)
	{
		if (lemin->start && lemin->end)
		{
			lemin->node = lemin->start;
			lemin->node->next = lemin->end;
		}
		else
		{
			free_lemin(lemin);
			exit(write(2, "ERROR! We don't have Start or End!\n", 35));
		}
	}
}
