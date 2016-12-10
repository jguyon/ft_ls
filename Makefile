# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jguyon <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/10 11:53:39 by jguyon            #+#    #+#              #
#    Updated: 2016/12/10 12:51:32 by jguyon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CC = gcc
CFLAGS = -Wall -Werror -Wextra
LD = $(CC)
LDFLAGS =

LIB_PATH = libft
LIB_NAME = ft
LIB = $(LIB_PATH)/lib$(LIB_NAME).a
LIB_INC_PATH = $(LIB_PATH)/includes
LIB_INC_NAMES = libft.h														\
				libftstream.h												\
				libftprintf.h

SRC_PATH = srcs
INC_PATH = includes
OBJ_PATH = objs

SRC_NAMES = main.c
INC_NAMES = ft_ls.h

INC = $(INC_NAMES:%.h=$(INC_PATH)/%.h) $(LIB_INC_NAMES:%.h=$(LIB_INC_PATH)/%.h)
OBJ = $(SRC_NAMES:%.c=$(OBJ_PATH)/%.o)

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $(filter %.o,$^) -L$(LIB_PATH) -l$(LIB_NAME)

$(LIB):
	make -C $(LIB_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INC)
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -I$(INC_PATH) -I$(LIB_INC_PATH) -o $@ -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
