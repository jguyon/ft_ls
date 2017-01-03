#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/03 12:54:24 by jguyon            #+#    #+#              #
#    Updated: 2017/01/03 13:19:10 by jguyon           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = gcc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS =
LIBS = -Llibft -lft
DEPFLAGS = -MMD -MP -MF $(patsubst $(OBJ_PATH)/%.o,$(DEP_PATH)/%.d,$@)

NAME = ft_ls

SRC_PATH = srcs
INC_PATH = includes
OBJ_PATH = objs
DEP_PATH = deps
LIB_PATH = libft
LIB_INC_PATH = $(LIB_PATH)/includes
LIB_NAME = $(LIB_PATH)/libft.a

SRC = $(wildcard $(SRC_PATH)/*.c)
OBJ = $(SRC:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)
DEP = $(SRC:$(SRC_PATH)/%.c=$(DEP_PATH)/%.d)

all: $(NAME)

$(NAME): $(LIB_NAME) $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(filter %.o,$^) $(LIBS)

$(LIB_NAME):
	make -C $(LIB_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(DEP_PATH)/%.d
	@mkdir -p $(dir $@) $(dir $(DEP_PATH)/$*)
	$(CC) $(CFLAGS) -I$(INC_PATH) -I$(LIB_INC_PATH) $(DEPFLAGS) -o $@ -c $<

$(DEP_PATH)/%.d: ;

-include $(DEP)

clean:
	make -C $(LIB_PATH) clean
	rm -f $(OBJ) $(DEP)

fclean: clean
	rm -f $(NAME) $(LIB_NAME)

re: fclean all

.PHONY: all clean fclean re
