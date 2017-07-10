/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_continue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 22:06:48 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/07/06 19:40:17 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	check_dublicate_name(t_lemin *lemin, char *str)
{
	int		i;
	char	*cp;
	t_node	*st;

	st = lemin->node;
	cp = str;
	while (st)
	{
		i = 0;
		while (!(ISSPACE(cp[i])) && ft_isascii(cp[i]))
		{
			if (st->name[i] == cp[i])
				i++;
			else
				break ;
		}
		if (st->name[i] == '\0' && ISSPACE(cp[i]))
		{
			free_lemin(lemin);
			exit(write(2, "ERROR! Dublicate room!\n", 23));
		}
		st = st->next;
	}
}

int		lemin_atoi(char **str, t_lemin *lemin)
{
	long	numb;
	int		n;

	numb = 0;
	n = 1;
	while (ISSPACE(**str))
		(*str)++;
	if (**str == '-')
	{
		n = -1;
		(*str)++;
	}
	while (ft_isdigit(**str))
		numb = numb * 10 + (*(*str)++ - '0');
	if (**str && **str != '\n' && !(ft_isdigit(**str)) && !(ISSPACE(**str)))
	{
		free_lemin(lemin);
		exit(write(2, "ERROR! Not valid arguments!\n", 28));
	}
	if (numb > 2147483647 || numb < -2147483648)
	{
		free_lemin(lemin);
		exit(write(2, "ERROR! Number is over or less INT!\n", 35));
	}
	return (numb * n);
}

void	write_name_x_y(char *str, t_node *node, t_lemin *lemin)
{
	int		i;
	char	*cp;

	i = 0;
	cp = str;
	if (*cp == 'L')
	{
		free_lemin(lemin);
		exit(write(2, "ERROR! Don't valid name!\n", 25));
	}
	while (!(ISSPACE(*cp)) && ft_isascii(*cp))
		node->name[i++] = *cp++;
	node->name[i] = '\0';
	node->x = lemin_atoi(&cp, lemin);
	node->y = lemin_atoi(&cp, lemin);
	check_x_y(lemin, node);
}

int		write_start_end(char *str, t_lemin *lemin, int flag)
{
	t_node	*tmp;

	(flag == 1) ? tmp = lemin->start : 0;
	(flag == 0) ? tmp = lemin->end : 0;
	if (tmp == NULL)
	{
		create_node(&tmp);
		tmp->name = (char*)malloc(sizeof(char) * length_name(str) + 1);
		write_name_x_y(str, tmp, lemin);
		if (flag == 1)
			tmp->st_en = 's';
		else if (flag == 0)
			tmp->st_en = 'e';
	}
	else
	{
		free_lemin(lemin);
		exit(write(2, "ERROR! Dublicate Start or End!\n", 31));
	}
	(flag == 1 && tmp) ? lemin->start = tmp : 0;
	(flag == 0 && tmp) ? lemin->end = tmp : 0;
	return (1);
}

void	write_coordinate(char *str, t_lemin *lemin)
{
	t_node	*st;

	st = lemin->node;
	check_dublicate_name(lemin, str);
	if (lemin->node)
	{
		while (lemin->node->next)
			lemin->node = lemin->node->next;
		create_node(&lemin->node->next);
		lemin->node->next->name =
		(char *)malloc(sizeof(char) * length_name(str) + 1);
		write_name_x_y(str, lemin->node->next, lemin);
	}
	else
	{
		create_node(&st);
		st->name = (char *)malloc(sizeof(char) * length_name(str) + 1);
		write_name_x_y(str, st, lemin);
	}
	lemin->node = st;
}
