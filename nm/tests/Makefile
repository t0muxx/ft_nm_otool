#
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/24 11:50:56 by tmaraval          #+#    #+#              #
#    Updated: 2019/10/24 12:04:17 by tmaraval         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

#NAME OF THE PROG#
NAME =			unit_tests.bin

#FLAG AND COMPILATOR#
CC =		clang
CFLAGS =  -g3 -fsanitize=address 

#PATH#
OBJ_PATH =  obj
SRC_PATH =  ./
INC_PATH :=  ./ -I../inc -I../../libft

ifeq ($(HOSTTYPE),x86_64_Darwin)
	INC_BREW = -I/Users/tmaraval/.brew/include
	LIB_BREW = -L/Users/tmaraval/.brew/lib
endif

SRCS = 	main.c \
		../src/command.c \
		../src/infile.c \
		./test_infile.c \
		../src/header.c \
		./test_header.c \
		../src/error.c \
	  	./test_segment.c \
		../src/segment.c \
		../src/lst_section.c

OBJ = $(SRC:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)
SRC = $(addprefix $(SRC_PATH)/,$(SRCS))

all: $(NAME) $(COVERAGE)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -I$(INC_PATH) $(INC_BREW) $(OBJ) $(LIB_BREW) -lcmocka ../../libft/libft.a -o $(NAME)

$(OBJ): $(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	mkdir -p $(dir $@)
	$(CC) -o $@ $(CFLAGS) -I$(INC_PATH) $(INC_BREW) -I../inc/ -c $<

clean:
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
