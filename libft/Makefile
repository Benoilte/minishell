#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/10 17:15:49 by bebrandt          #+#    #+#              #
#    Updated: 2024/07/01 13:07:36 by bebrandt         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

# Library name

NAME			=	libft.a

# object directory

OBJ_DIR			=	objs/

# libft ressources

LIBFT_DIR		=	libft_srcs/
LIBFT_SRCS		=	$(addprefix $(LIBFT_DIR), ft_atoi.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
					ft_isdigit.c ft_isprint.c ft_isspace.c ft_strchr.c ft_strlcpy.c ft_strlen.c \
					ft_strncmp.c ft_my_strcmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c \
					ft_toupper.c ft_strlcat.c ft_memset.c ft_memcpy.c ft_memmove.c ft_memcmp.c \
					ft_memchr.c ft_bzero.c ft_strdup.c ft_calloc.c ft_substr.c ft_strjoin.c \
					ft_strtrim.c ft_split.c ft_itoa.c ft_itoa_hex.c ft_itoa_uint.c \
					ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
					ft_putnbr_hex_fd.c ft_putnbr_uint_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
					ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
					ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
					ft_atoli.c ft_atoh.c)

# gnl ressources

GNL_DIR			=	gnl_srcs/
GNL_SRCS		=	$(addprefix $(GNL_DIR), ft_get_next_line.c ft_get_next_line_utils.c)

# ft_printf ressources

FT_PRINTF_DIR	=	ft_printf_srcs/
FT_PRINTF_SRCS	=	$(addprefix $(FT_PRINTF_DIR), ft_printf.c flag_utils.c ft_is_specifier.c \
					ft_print_char.c ft_print_str.c ft_print_int.c ft_print_uint.c \
					ft_print_arg.c ft_print_hex.c ft_print_ptr.c ft_print_percent.c \
					ft_print_decimal.c ft_print_width_fd.c ft_print_precision_fd.c \
					ft_print_hex_format.c set_lst.c)

# Object creations

SRCS			=	$(LIBFT_SRCS) $(GNL_SRCS) $(FT_PRINTF_SRCS)
OBJS			=	$(patsubst %.c, $(OBJ_DIR)%.o, $(notdir $(SRCS)));

# headers directories

HDRS			=	-Iincludes/.

# usefull command

CC				=	gcc $(HDRS)
CFLAGS			=	-Wall -Wextra -Werror -g
AR				=	ar rcs
RM				=	rm -f


RED			=	\033[0;31m
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
NONE		=	\033[0m

VPATH			=	 $(LIBFT_DIR):$(GNL_DIR):$(FT_PRINTF_DIR)

all:	$(NAME)

# rule to create libft object

$(OBJ_DIR)%.o:	%.c
	@mkdir -p $(OBJ_DIR)
	@printf "$(YELLOW).$(NONE)"
	@$(CC) $(CFLAGS) -c $< -o $@

# program compilation

$(NAME):	$(OBJS)
	@$(AR) $(NAME) $^

# usefull rules

clean:
	@$(RM) $(OBJS)
	@echo "$(RED)##### Removed libft object files #####$(NONE)"

fclean:	clean
	@$(RM) $(NAME)
	@echo "$(RED)##### Removed libft binary file #####$(NONE)"

re:	fclean all

.PHONY: all clean fclean re
