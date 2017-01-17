#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/03 12:54:24 by jguyon            #+#    #+#              #
#    Updated: 2017/01/17 12:01:56 by jguyon           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = gcc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS =
LIBS = -Llibft -lft
DEPFLAGS = -MMD -MP -MF $(patsubst $(OBJ_PATH)/%.o,$(DEP_PATH)/%.d,$@)

NAME = ft_ls
TST_NAME = run_tests

SRC_PATH = srcs
TST_PATH = tests
INC_PATH = includes
OBJ_PATH = objs
DEP_PATH = deps
LIB_PATH = libft
LIB_INC_PATH = $(LIB_PATH)/includes
LIB_NAME = $(LIB_PATH)/libft.a

SRC = $(wildcard $(SRC_PATH)/*.c)
OBJ = $(SRC:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)
DEP = $(SRC:$(SRC_PATH)/%.c=$(DEP_PATH)/%.d)

TST_SRC = $(wildcard $(TST_PATH)/*.c)
TST_OBJ = $(TST_SRC:$(TST_PATH)/%.c=$(OBJ_PATH)/$(TST_PATH)/%.o)
TST_DEP = $(TST_SRC:$(TST_PATH)/%.c=$(DEP_PATH)/$(TST_PATH)/%.d)

all: lib $(NAME)

lib:
	@make -C $(LIB_PATH)

test: CFLAGS += -g
test: LDFLAGS += -g
test: lib $(TST_NAME)
	./$<

$(NAME): $(LIB_NAME) $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(filter %.o,$^) $(LIBS)

$(TST_NAME): $(LIB_NAME) $(filter-out $(OBJ_PATH)/main.o,$(OBJ)) $(TST_OBJ)
	$(CC) $(LDFLAGS) -o $@ $(filter %.o,$^) $(LIBS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(DEP_PATH)/%.d
	@mkdir -p $(dir $@) $(dir $(DEP_PATH)/$*)
	$(CC) $(CFLAGS) -I$(INC_PATH) -I$(LIB_INC_PATH) $(DEPFLAGS) -o $@ -c $<

$(OBJ_PATH)/$(TST_PATH)/%.o: $(TST_PATH)/%.c $(DEP_PATH)/$(TST_PATH)/%.d
	@mkdir -p $(dir $@) $(dir $(DEP_PATH)/$(TST_PATH)/$*)
	$(CC) $(CFLAGS) -I$(INC_PATH) -I$(LIB_INC_PATH) $(DEPFLAGS) -o $@ -c $<

$(DEP_PATH)/%.d: ;

-include $(DEP) $(TST_DEP)

clean:
	make -C $(LIB_PATH) clean
	rm -f $(OBJ) $(DEP) $(TST_OBJ) $(TST_DEP)

fclean: clean
	rm -f $(NAME) $(LIB_NAME)

re: fclean all

.PHONY: all test lib clean fclean re
