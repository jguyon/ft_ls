#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2016/12/10 11:53:39 by jguyon            #+#    #+#             *#
#*   Updated: 2016/12/12 20:09:18 by jguyon           ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

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

SRC_NAMES = ls_streams.c													\
			ls_set_progname.c												\
			ls_open_streams.c												\
			ls_close_streams.c												\
			ls_printf_out.c													\
			ls_printf_err.c													\
			ls_parse_args.c													\
			ls_destroy_args.c												\
			ls_list_files.c													\
			ls_print_files.c												\
			ls_destroy_files.c												\
			ls_join_path.c													\
			ls_lexi_cmp.c													\
			ls_modt_cmp.c													\
			ls_lexi_revcmp.c												\
			ls_modt_revcmp.c												\
			main.c
INC_NAMES = ft_ls.h

INC = $(INC_NAMES:%.h=$(INC_PATH)/%.h) $(LIB_INC_NAMES:%.h=$(LIB_INC_PATH)/%.h)
OBJ = $(SRC_NAMES:%.c=$(OBJ_PATH)/%.o)
OBJDIR = $(OBJ_PATH)

TST_NAME = test_ls
TST_PATH = tests
TST_SRC_NAMES = test_streams.c												\
				test_parse_args.c											\
				test_list_files.c											\
				test_print_files.c											\
				test_utils.c												\
				main.c
TST_INC_NAMES = test_ls.h
TST_INC = $(TST_INC_NAMES:%.h=$(INC_PATH)/$(TST_PATH)/%.h)
TST_OBJ = $(filter-out $(OBJ_PATH)/main.o,$(OBJ))							\
		  $(TST_SRC_NAMES:%.c=$(OBJ_PATH)/$(TST_PATH)/%.o)
TST_CFLAGS = -g
TST_LDFLAGS = -g
TST_OBJDIR = $(OBJ_PATH)/$(TST_PATH)

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $(filter %.o,$^) -L$(LIB_PATH) -l$(LIB_NAME)

$(LIB):
	make -C $(LIB_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INC) $(TST_INC)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INC_PATH) -I$(LIB_INC_PATH) -o $@ -c $<

test: CFLAGS += $(TST_CFLAGS)
test: LDFLAGS += $(TST_LDFLAGS)
test: INC += $(TST_INC)
test: OBJDIR += $(TST_OBJDIR)
test: $(TST_NAME)
	./$<

$(TST_NAME): $(LIB) $(TST_OBJ)
	$(LD) $(LDFLAGS) -o $@ $(filter %.o,$^) -L$(LIB_PATH) -l$(LIB_NAME)

clean:
	rm -f $(OBJ) $(TST_SRC_NAMES:%.c=$(OBJ_PATH)/$(TST_PATH)/%.o) $(TST_NAME)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test
