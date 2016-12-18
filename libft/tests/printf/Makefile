#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2016/12/09 23:23:22 by jguyon            #+#    #+#             *#
#*   Updated: 2016/12/09 23:29:28 by jguyon           ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME = test_printf

CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wno-format
LD = gcc
LDFLAGS =

LIB_PATH = ../..
LIB_NAME = ft
LIB = $(LIB_PATH)/lib$(LIB_NAME).a
LIB_INCLUDES = $(LIB_PATH)/includes

HDR = test_printf.h $(LIB_INCLUDES)/libftprintf.h
SRC = main.c																\
	  test_basics.c															\
	  test_ints.c															\
	  test_strings.c														\
	  test_ptr.c															\
	  test_args.c															\
	  test_err.c
OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	$(LD) $(LDFLAGS) $(filter %.o,$^) -o $@ -L$(LIB_PATH) -l$(LIB_NAME)

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -o $@ -c $< -I$(LIB_INCLUDES)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
