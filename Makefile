# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 11:59:35 by bebrandt          #+#    #+#              #
#    Updated: 2024/05/14 11:12:59 by bebrandt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=

SRCS_DIR	=	srcs/

SRCS	=	$(addsuffix .c, )

OBJ 	= $(FDF_SRCS:.c=.o)

OBJS 	= $(addprefix $(OBJ_DIR),$(FDF_OBJ))

LIBFT_DIR	=	libft/

LIBFT_NAME	=	libft.a

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror -g

RM			=	rm -f

OBJ_DIR		=	objs/


RED			=	\033[0;31m
GREEN		=	\033[0;32m
NONE		=	\033[0m

all: $(LIBFT_DIR)$(LIBFT_NAME) $(NAME)

$(NAME): $(FDF_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIBFT_DIR) -lft

$(LIBFT_DIR)$(LIBFT_NAME):
	@make -C $(LIBFT_DIR) all

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(OS_FLAGS) -c -o $@ $< $(INCLUDES)
	@echo "$(GREEN)##### Creating" [ $@ ] " #####$(NONE)"

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	@rm -f $(FDF_OBJS)
	@echo "$(RED)##### Removed object files #####$(NONE)"

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@make -C $(MLX_DIR) clean
	@rm -f $(NAME)
	@echo "$(RED)##### Removed binary files #####$(NONE)"

re: fclean all

.PHONY: all clean fclean re
