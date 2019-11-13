# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/24 11:50:56 by tmaraval          #+#    #+#              #
#    Updated: 2019/11/13 09:22:00 by tmaraval         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME =			ft_nm

#FLAG AND COMPILATOR#
CC =		clang
CFLAGS =  -Wall -Werror -Wextra -g3

#PATH#
OBJ_PATH =  obj
SRC_PATH =  src
INC_PATH =  inc
INC_LIBFT = ../libft

ifeq ($(HOSTTYPE),x86_64_Linux)
	INC_MACHO = -I../mach_headers/
endif

SRCS = 	infile.c \
		command.c \
		error.c \
		header.c \
		segment.c \
		lst_section.c \
		lst_symbol.c \
		symbol.c \
		symbol_resolve.c \
		reverse_bytes.c \
		fat.c \
		fat_utils.c \
		archive.c \
		archive_utils.c \
		protect.c \
		print.c \
		main.c

OBJ = $(SRC:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)
SRC = $(addprefix $(SRC_PATH)/,$(SRCS))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -I$(INC_PATH) -I$(INC_LIBFT) $(INC_MACHO) $(OBJ) ../libft/libft.a -o $(NAME)
	/bin/rm -f $(LINK)

$(OBJ): $(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	mkdir -p $(dir $@)
	$(CC) -o $@ $(CFLAGS) -I$(INC_PATH) -I$(INC_LIBFT) $(INC_MACHO) -c $<

clean:
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
