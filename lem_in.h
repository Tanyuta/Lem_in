/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 19:44:16 by tprysiaz          #+#    #+#             */
/*   Updated: 2017/07/07 18:14:49 by tprysiaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/includes/libft.h"
# define ISSPACE(x) (x == ' ' || x == '\t' || x == '\r' || x == '\v')

typedef struct		s_read
{
	char			*str;
	struct s_read	*next;
}					t_read;

typedef struct		s_node
{
	int				index;
	int				ret;
	int				flag;
	int				depth;
	int				ant;
	int				nbr;
	int				x;
	int				y;
	char			st_en;
	char			*name;
	struct s_node	**link;
	struct s_node	*next;
}					t_node;

typedef struct		s_lemin
{
	int				a;
	int				all_ants;
	int				lst_len;
	int				roads;
	int				**matrix;
	int				**ways;
	t_node			*node;
	t_node			*start;
	t_node			*end;
	t_read			*lst;
}					t_lemin;
/*
** lem_in
*/
void				lemin_read(t_lemin *lemin);
t_read				*initializer(t_lemin *lemin, int flag);
void				lemin_write(t_lemin *lemin);
void				check_map(t_lemin *lemin, t_read **st, int *flag);
/*
** lem_in_continue
*/
void				write_coordinate(char *str, t_lemin *lemin);
int					write_start_end(char *str, t_lemin *lemin, int flag);
void				write_name_x_y(char *str, t_node *node, t_lemin *lemin);
int					lemin_atoi(char **str, t_lemin *lemin);
void				check_dublicate_name(t_lemin *lemin, char *str);
/*
** algorithm
*/
void				write_matrix(t_lemin *lemin);
void				lemin_funcs(t_lemin *lemin);
int					write_depth(t_node *st, t_lemin *lemin, int d);
void				write_road(t_lemin *lemin, int *way, int len);
void				initialize_way(t_lemin *lemin, int len, int *way);
/*
** algorithm_continue
*/
void				add_start_end(t_lemin *lemin);
void				search_name_links_s1(char *str, t_lemin *lemin);
void				search_name_links_s2(char *str, t_lemin *lemin, t_node *s1);
void				write_link(t_node *s1, t_node *s2, t_lemin *lemin);
void				write_link_2(t_node *s1, t_node *s2, t_lemin *lemin);
/*
** run_ants
*/
void				distribution_of_ants(t_lemin *lemin, int n);
void				distribution_of_ants_2(t_lemin *lemin, t_node *st1,
											t_node *st2, int i[2]);
void				distribution_of_ants_3(t_node *st1, t_node *st2);
int					run_ants(t_lemin *lemin, int n);
int					count_ants_for_ways(t_lemin *lemin);
/*
** work_with_nodes
*/
void				create_node(t_node **node);
int					list_size(t_node *list);
void				index_list(t_node *st);
void				depth_zero(t_lemin *lemin);
t_node				*search_node(t_lemin *lemin, int n);
/*
** addition_funcs
*/
void				check_x_y(t_lemin *lemin, t_node *node);
int					length_name(char *str);
void				str_reverse(int *way, int len);
int					count_words(char *str);
int					max_roads(t_lemin *lemin);
/*
** print_map_and_all_free
*/
void				print_map(t_lemin *lemin);
void				free_read(t_read *read);
void				free_node(t_node *node);
void				free_lemin(t_lemin *lemin);
int					ft_count_roads(t_lemin *lemin);

#endif
