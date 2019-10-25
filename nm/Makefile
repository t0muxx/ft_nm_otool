# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/24 11:50:56 by tmaraval          #+#    #+#              #
#    Updated: 2019/10/25 09:24:29 by tmaraval         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME =			ft_nm

#FLAG AND COMPILATOR#
CC =		clang
CFLAGS =  -g -Wall -Werror -Wextra -fsanitize=address

#PATH#
OBJ_PATH =  obj
SRC_PATH =  src
INC_PATH =  inc
INC_LIBFT = ../libft

ifeq ($(HOSTTYPE),x86_64_Linux)
	INC_MACHO = ../mach_headers/
endif

SRCS = 	main.c \
		infile.c \
		command.c \
		error.c \
		header.c \
		segment.c \
		lst_section.c \
		lst_symbol.c \
		symbol.c \
		symbol_resolve.c

OBJ = $(SRC:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)
SRC = $(addprefix $(SRC_PATH)/,$(SRCS))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -I$(INC_PATH) -I$(INC_LIBFT) -I$(INC_MACHO) $(OBJ) ../libft/libft.a -o $(NAME)
	/bin/rm -f $(LINK)

$(OBJ): $(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	mkdir -p $(dir $@)
	$(CC) -o $@ $(CFLAGS) -I$(INC_PATH) -I$(INC_LIBFT) -I$(INC_MACHO) -c $<

clean:
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
