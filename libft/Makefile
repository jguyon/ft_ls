#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/17 15:12:56 by jguyon            #+#    #+#              #
#    Updated: 2017/01/17 21:21:49 by jguyon           ###   ########.fr        #
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

SRC_NAMES =	\
	memory/ft_memalloc \
	memory/ft_memdel \
	memory/ft_memchr \
	memory/ft_memcmp \
	memory/ft_memset \
	memory/ft_bzero \
	memory/ft_memcpy \
	memory/ft_memccpy \
	memory/ft_memmove \
	\
	strings/ft_strnew \
	strings/ft_strdel \
	strings/ft_strdup \
	strings/ft_strsub \
	strings/ft_strjoin \
	strings/ft_strtrim \
	strings/ft_strsplit \
	strings/ft_strlen \
	strings/ft_strnlen \
	strings/ft_strchr \
	strings/ft_strrchr \
	strings/ft_strchrnul \
	strings/ft_strstr \
	strings/ft_strnstr \
	strings/ft_strcmp \
	strings/ft_strncmp \
	strings/ft_strequ \
	strings/ft_strnequ \
	strings/ft_strclr \
	strings/ft_strcpy \
	strings/ft_strncpy \
	strings/ft_strcat \
	strings/ft_strncat \
	strings/ft_strlcat \
	\
	chars/ft_isalpha \
	chars/ft_isdigit \
	chars/ft_isalnum \
	chars/ft_isascii \
	chars/ft_isprint \
	chars/ft_toupper \
	chars/ft_tolower \
	\
	numbers/ft_atoi \
	numbers/ft_itoa \
	\
	unicode/ft_wcconv \
	unicode/ft_wclen \
	unicode/ft_wstrlen \
	\
	dlists/ft_dlst_init \
	dlists/ft_dlst_insertl \
	dlists/ft_dlst_insertr \
	dlists/ft_dlst_pushl \
	dlists/ft_dlst_pushr \
	dlists/ft_dlst_remove \
	dlists/ft_dlst_popl \
	dlists/ft_dlst_popr \
	dlists/ft_dlst_replace \
	dlists/ft_dlst_swap \
	dlists/ft_dlst_slice \
	dlists/ft_dlst_splicel \
	dlists/ft_dlst_splicer \
	dlists/ft_dlst_joinl \
	dlists/ft_dlst_joinr \
	dlists/ft_dlst_prev \
	dlists/ft_dlst_next \
	dlists/ft_dlst_first \
	dlists/ft_dlst_last \
	dlists/ft_dlst_empty \
	dlists/ft_dlst_singular \
	dlists/ft_dlst_foreachl \
	dlists/ft_dlst_foreachr \
	dlists/ft_dlst_foreachl_from \
	dlists/ft_dlst_foreachr_from \
	dlists/ft_dlst_sort \
	\
	streams/ft_std \
	streams/ft_fopencookie \
	streams/ft_setbuffer \
	streams/ft_fwrite \
	streams/ft_fputc \
	streams/ft_fputs \
	streams/ft_ferror \
	streams/ft_clearerr \
	streams/ft_fclose \
	streams/ft_fflush \
	\
	printf/ft_printf \
	printf/ft_vprintf \
	printf/ft_dprintf \
	printf/ft_vdprintf \
	printf/ft_sprintf \
	printf/ft_vsprintf \
	printf/ft_snprintf \
	printf/ft_vsnprintf \
	printf/ft_fprintf \
	printf/ft_vfprintf \
	printf/pf_parse_info \
	printf/pf_convert \
	printf/pf_convert_char \
	printf/pf_convert_str \
	printf/pf_convert_int \
	printf/pf_convert_uint \
	printf/pf_convert_ptr \
	printf/pf_uintmax_len \
	printf/pf_write_pad \
	printf/pf_write_str \
	printf/pf_write_wstr \
	printf/pf_write_uint \

TST_NAMES = \
	main \
	test_strings \
	test_dlists \
	test_streams \
	test_printf \

SRC_PATH = srcs
TST_PATH = tests
INC_PATH = includes
OBJ_PATH = objs
DEP_PATH = deps

SRC = $(SRC_NAMES:%=$(SRC_PATH)/%.c)
OBJ = $(SRC:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)
DEP = $(SRC:$(SRC_PATH)/%.c=$(DEP_PATH)/%.d)

TST_SRC = $(TST_NAMES:%=$(TST_PATH)/%.c)
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
