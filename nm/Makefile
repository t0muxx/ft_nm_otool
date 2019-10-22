# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/24 11:50:56 by tmaraval          #+#    #+#              #
#    Updated: 2019/10/22 15:55:25 by tmaraval         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			ft_nm

#FLAG AND COMPILATOR#
CC =		clang
CFLAGS =  -g -Wall -Werror -Wextra -fPIC 

#PATH#
OBJ_PATH =  obj
SRC_PATH =  src
INC_PATH =  inc
INC_LIBFT = ../libft/

SRCS = main.c \

OBJ = $(SRC:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)
SRC = $(addprefix $(SRC_PATH)/,$(SRCS))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -I$(INC_PATH) -I$(INC_LIBFT) $(OBJ) ../libft/libft.a -o $(NAME)
	/bin/rm -f $(LINK)
	ln -s $(NAME) $(LINK)

$(OBJ): $(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	mkdir -p $(dir $@)
	$(CC) -o $@ $(CFLAGS) -I$(INC_PATH) -c $<

clean:
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
