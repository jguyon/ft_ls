#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2016/12/09 17:07:08 by jguyon            #+#    #+#             *#
#*   Updated: 2016/12/09 18:33:08 by jguyon           ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME = test_libft

CC = gcc
CFLAGS = -Wall -Werror -Wextra
LD = $(CC)
LDFLAGS =

LIB_PATH = ..
LIB_NAME = ft
LIB = $(LIB_PATH)/lib$(LIB_NAME).a
LIB_INC_PATH = $(LIB_PATH)/includes
LIB_INC_NAMES = libft.h

SRC = main.c																\
	  test_lists.c
INC = test_libft.h $(LIB_INC_NAMES:%.h=$(LIB_INC_PATH)/%.h)
OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $(filter %.o,$^) -L$(LIB_PATH) -l$(LIB_NAME)

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -I$(LIB_INC_PATH) -o $@ -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
