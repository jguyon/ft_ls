#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/17 15:12:56 by jguyon            #+#    #+#              #
#    Updated: 2017/01/03 12:16:59 by jguyon           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = gcc
AR = ar
CFLAGS = -Wall -Werror -Wextra
LDFLAGS =
LIBS =
DEPFLAGS = -MMD -MP -MF $(patsubst $(OBJ_PATH)/%.o,$(DEP_PATH)/%.d,$@)

NAME = libft.a
TST_NAME = run_tests

SRC_PATH = srcs
TST_PATH = tests
INC_PATH = includes
OBJ_PATH = objs
DEP_PATH = deps

SRC = $(wildcard $(SRC_PATH)/*/*.c)
OBJ = $(SRC:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)
DEP = $(SRC:$(SRC_PATH)/%.c=$(DEP_PATH)/%.d)

TST_SRC = $(wildcard $(TST_PATH)/*.c)
TST_OBJ = $(TST_SRC:$(TST_PATH)/%.c=$(OBJ_PATH)/$(TST_PATH)/%.o)
TST_DEP = $(TST_SRC:$(TST_PATH)/%.c=$(DEP_PATH)/$(TST_PATH)/%.d)

all: $(NAME)

test: CFLAGS += -g -Wno-format
test: LDFLAGS += -g
test: $(TST_NAME)
	./$<

$(NAME): $(OBJ)
	$(AR) rcs $@ $^

$(TST_NAME): $(OBJ) $(TST_OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(DEP_PATH)/%.d
	@mkdir -p $(dir $@) $(dir $(DEP_PATH)/$*)
	$(CC) $(CFLAGS) -I$(INC_PATH) $(DEPFLAGS) -o $@ -c $<

$(OBJ_PATH)/$(TST_PATH)/%.o: $(TST_PATH)/%.c $(DEP_PATH)/$(TST_PATH)/%.d
	@mkdir -p $(dir $@) $(dir $(DEP_PATH)/$(TST_PATH)/$*)
	$(CC) $(CFLAGS) -I$(INC_PATH) $(DEPFLAGS) -o $@ -c $<

$(DEP_PATH)/%.d: ;

-include $(DEP) $(TST_DEP)

clean:
	rm -f $(OBJ) $(DEP) $(TST_OBJ) $(TST_DEP)

fclean: clean
	rm -f $(NAME) $(TST_NAME)

re: fclean all

.PHONY: all test clean fclean re
