#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2016/11/17 15:12:56 by jguyon            #+#    #+#             *#
#    Updated: 2016/12/30 16:23:50 by jguyon           ###   ########.fr        #
#*                                                                            *#
#* ************************************************************************** *#

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra
AR = ar

SRC_PATH = srcs
SRC_FILES = ft_memset.c														\
			ft_bzero.c														\
			ft_memcpy.c														\
			ft_memccpy.c													\
			ft_memmove.c													\
			ft_memchr.c														\
			ft_memcmp.c														\
			ft_strlen.c														\
			ft_strnlen.c													\
			ft_strdup.c														\
			ft_strcpy.c														\
			ft_strncpy.c													\
			ft_strcat.c														\
			ft_strncat.c													\
			ft_strlcat.c													\
			ft_strchr.c														\
			ft_strrchr.c													\
			ft_strchrnul.c													\
			ft_strstr.c														\
			ft_strnstr.c													\
			ft_strcmp.c														\
			ft_strncmp.c													\
			ft_atoi.c														\
			ft_isalpha.c													\
			ft_isdigit.c													\
			ft_isalnum.c													\
			ft_isascii.c													\
			ft_isprint.c													\
			ft_toupper.c													\
			ft_tolower.c													\
																			\
			ft_memalloc.c													\
			ft_memdel.c														\
			ft_strnew.c														\
			ft_strdel.c														\
			ft_strclr.c														\
			ft_striter.c													\
			ft_striteri.c													\
			ft_strmap.c														\
			ft_strmapi.c													\
			ft_strequ.c														\
			ft_strnequ.c													\
			ft_strsub.c														\
			ft_strjoin.c													\
			ft_strtrim.c													\
			ft_strsplit.c													\
			ft_itoa.c														\
			ft_uimtoa_base.c												\
			ft_putchar_fd.c													\
			ft_putstr_fd.c													\
			ft_putendl_fd.c													\
			ft_putnbr_fd.c													\
			ft_putchar.c													\
			ft_putstr.c														\
			ft_putendl.c													\
			ft_putnbr.c														\
																			\
			ft_lstnew.c														\
			ft_lstdelone.c													\
			ft_lstdel.c														\
			ft_lstdelcnt.c													\
			ft_lstadd.c														\
			ft_lstiter.c													\
			ft_lstmap.c														\
			ft_lstfoldl.c													\
			ft_lstfoldr.c													\
			ft_lstsort.c													\
			ft_lstmsort.c													\
																			\
			ft_wcconv.c														\
			ft_wclen.c														\
			ft_wstrlen.c													\
																			\
			stream/ft_fopencookie.c											\
			stream/ft_fwrite.c												\
			stream/ft_fputc.c												\
			stream/ft_fputs.c												\
			stream/ft_ferror.c												\
			stream/ft_fclose.c												\
			stream/ft_fflush.c												\
																			\
			printf/pf_arg_char.c											\
			printf/pf_arg_fmt.c												\
			printf/pf_arg_int.c												\
			printf/pf_arg_ptr.c												\
			printf/pf_arg_str.c												\
			printf/pf_arg_uint.c											\
			printf/pf_clean_str.c											\
			printf/pf_del_convs.c											\
			printf/pf_extract_args.c										\
			printf/pf_format_int.c											\
			printf/pf_format_ptr.c											\
			printf/pf_format_str.c											\
			printf/pf_get_format.c											\
			printf/pf_get_info.c											\
			printf/pf_parse_format.c										\
			printf/pf_write_convs.c											\
			printf/ft_printf.c												\
			printf/ft_vprintf.c												\
			printf/ft_dprintf.c												\
			printf/ft_vdprintf.c											\
			printf/ft_fprintf.c												\
			printf/ft_vfprintf.c

HDR_PATH = includes
HDR_FILES = libft.h															\
			libftstream.h													\
			libftprintf.h													\
			priv/pf_utils.h

TEST_NAME = test_libft
TEST_PATH = tests

OBJ_PATH = objs
OBJ_FILES = $(SRC_FILES:%.c=%.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_FILES))
HDR = $(addprefix $(HDR_PATH)/,$(HDR_FILES))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_FILES))

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) rcs $@ $^

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HDR)
	@mkdir -p $(OBJ_PATH)/stream $(OBJ_PATH)/printf
	$(CC) $(CFLAGS) -I$(HDR_PATH) -o $@ -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: test_lib test_printf

test_lib: all
	@make NAME=$(TEST_NAME) -C $(TEST_PATH)
	./$(TEST_PATH)/$(TEST_NAME)

test_printf: all
	@make NAME=$(TEST_NAME) -C $(TEST_PATH)/printf
	./$(TEST_PATH)/printf/$(TEST_NAME)

.PHONY: all clean fclean re
