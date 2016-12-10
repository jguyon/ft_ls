# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jguyon <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/10 11:53:39 by jguyon            #+#    #+#              #
#    Updated: 2016/12/10 12:01:06 by jguyon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CC = gcc
CFLAGS = -Wall -Werror -Wextra
LD = $(CC)
LDFLAGS =

SRC_PATH = srcs
INC_PATH = includes
OBJ_PATH = objs

SRC_NAMES = main.c
INC_NAMES = ft_ls.h

INC = $(INC_NAMES:%.h=$(INC_PATH)/%.h)
OBJ = $(SRC_NAMES:%.c=$(OBJ_PATH)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INC)
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -I$(INC_PATH) -o $@ -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
