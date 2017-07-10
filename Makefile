# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tprysiaz <tprysiaz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/15 20:34:05 by tprysiaz          #+#    #+#              #
#    Updated: 2017/07/06 20:16:50 by tprysiaz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

FLAGS = -Wall -Wextra -Werror -O3

SRC = 	lem_in.c algorithm.c run_ants.c work_with_nodes.c lem_in_continue.c \
		print_map_and_all_free.c addition_funcs.c algorithm_continue.c

OBJ = $(patsubst %.c, %.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/
	@clang $(FLAGS) -o $@ $(SRC) libft/libft.a
	@rm -r $(OBJ)

%.o: %.c
	@clang $(FLAGS) -I libft/includes -o $@ -c $<

clean:
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C ./libft
	@rm -f $(OBJ) $(NAME)

re: fclean all
