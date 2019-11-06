# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/24 11:50:56 by tmaraval          #+#    #+#              #
#    Updated: 2019/11/06 15:31:17 by tmaraval         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			ft_nm&ft_otool
NAME_NM =		ft_nm
NAME_OTOOL =	ft_otool

#FLAG AND COMPILATOR#
CC =		clang
CFLAGS =  -Wall -Werror -Wextra -g3 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJ)
	@+$(MAKE) -C libft/
	@+$(MAKE) -C nm/
	@+$(MAKE) -C otool/
	cp nm/$(NAME_NM) .
	cp otool/$(NAME_OTOOL) .
	

clean:
	@+$(MAKE) clean -C libft/
	@+$(MAKE) clean -C nm/
	@+$(MAKE) clean -C otool/

fclean: clean
	@+$(MAKE) fclean -C libft/
	@+$(MAKE) fclean -C nm/
	@+$(MAKE) fclean -C otool/
	/bin/rm -f $(NAME_NM) $(NAME_OTOOL)

re: fclean all

.PHONY: all clean fclean re
