#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/03 12:54:24 by jguyon            #+#    #+#              #
#    Updated: 2017/01/29 14:32:18 by jguyon           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = gcc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS =
LIBS = -Llibft -lft
ifeq ($(shell uname),Linux)
	LIBS += -lacl
endif
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

SRC_NAMES = \
	ls_setprogname \
	ls_getprogname \
	ls_atexit \
	ls_cleanup \
	ls_exit \
	ls_warn \
	ls_warnx \
	ls_err \
	ls_errx \
	ls_vwarn \
	ls_vwarnx \
	ls_verr \
	ls_verrx \
	ls_getopt \
	\
	ls_cache_get \
	ls_cache_clear \
	\
	ls_istty \
	ls_tty_width \
	\
	ls_file_stat \
	ls_file_type \
	ls_file_del \
	ls_flist_init \
	ls_flist_add \
	ls_flist_start \
	ls_flist_next \
	ls_flist_print \
	ls_flist_clear \
	\
	ls_print_name \
	ls_print_suffix \
	ls_file_error \
	ls_insert_lstat \
	ls_reject_hidden \
	ls_compare_lexi \
	ls_compare_time \
	ls_compare_size \
	ls_print_line \
	ls_init_long \
	ls_insert_long \
	ls_print_long \
	ls_print_total \
	ls_get_time \
	ls_init_cols \
	ls_insert_cols \
	ls_print_cols \
	\
	ls_extended_chr \
	ls_get_owner \
	ls_get_group \
	ls_format_mode \
	ls_format_time \
	ls_read_target \
	\
	ls_parse_flags \
	ls_parse_files \
	ls_print_files \
	ls_cleanup_files \
	\
	main \

TST_NAMES = \
	main \
	test_program \
	test_cache \
	test_files \
	test_callbacks \

SRC = $(SRC_NAMES:%=$(SRC_PATH)/%.c)
OBJ = $(SRC:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)
DEP = $(SRC:$(SRC_PATH)/%.c=$(DEP_PATH)/%.d)

TST_SRC = $(TST_NAMES:%=$(TST_PATH)/%.c)
TST_OBJ = $(TST_SRC:$(TST_PATH)/%.c=$(OBJ_PATH)/$(TST_PATH)/%.o)
TST_DEP = $(TST_SRC:$(TST_PATH)/%.c=$(DEP_PATH)/$(TST_PATH)/%.d)

all: $(NAME)

test: CFLAGS += -g
test: LDFLAGS += -g
test: $(TST_NAME)
	./$(TST_NAME)

$(NAME): $(LIB_NAME) $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(filter %.o,$^) $(LIBS)

$(TST_NAME): $(LIB_NAME) $(filter-out $(OBJ_PATH)/main.o,$(OBJ)) $(TST_OBJ)
	$(CC) $(LDFLAGS) -o $@ $(filter %.o,$^) $(LIBS)

$(LIB_NAME): force
	@make -C $(LIB_PATH)

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
	rm -f $(NAME) $(LIB_NAME) $(TST_NAME)

re: fclean all

.PHONY: all test force clean fclean re
