# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 11:59:35 by bebrandt          #+#    #+#              #
#    Updated: 2024/05/20 18:52:28 by bebrandt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell

MAIN				=
SRCS_DIR			=	srcs/
OBJ_DIR				=	objs/

# main ressources

MAIN_DIR			=	$(SRCS_DIR)main/

ifeq ($(MAIN), ben)
	MAIN_SRCS		+=	$(addprefix $(MAIN_DIR), $(addsuffix .c, main_ben))
else ifeq ($(MAIN), tom)
	MAIN_SRCS		+=	$(addprefix $(MAIN_DIR), $(addsuffix .c, main_tom))
else
	MAIN_SRCS		+=	$(addprefix $(MAIN_DIR), $(addsuffix .c, minishell))
endif

MAIN_SRCS			+=	$(addprefix $(MAIN_DIR), $(addsuffix .c, prompt))

# lexer ressources

LEXER_DIR			=	$(SRCS_DIR)lexer/
LEXER_SRCS			=	$(addprefix $(LEXER_DIR), $(addsuffix .c, lexer lexer_cmd \
						lexer_redirections lexer_get_str lexer_define_type))

# parser ressources

PARSER_DIR			=	$(SRCS_DIR)parser/
PARSER_SRCS			=	$(addprefix $(PARSER_DIR), $(addsuffix .c, parser parser_utils \
						parser_check_redirections parser_check_cmd \
						parser_update_data))

# builtins ressources

BUILTINS_DIR		=	$(SRCS_DIR)builtins/
BUILTINS_SRCS		=	$(addprefix $(BUILTINS_DIR), $(addsuffix .c, builtins))

# exec ressources

EXEC_DIR			=	$(SRCS_DIR)exec/
EXEC_SRCS			=	$(addprefix $(EXEC_DIR), $(addsuffix .c, exec))

# struct_utils ressources

STRUCT_UTILS_DIR	=	$(SRCS_DIR)struct_utils/
STRUCT_UTILS_SRCS	=	$(addprefix $(STRUCT_UTILS_DIR), $(addsuffix .c, init new add_back \
						last clear_one clear_all env_utils))

# test ressources

TEST_DIR			=	$(SRCS_DIR)test/
TEST_SRCS			=	$(addprefix $(TEST_DIR), $(addsuffix .c, test))

# sources and objects variables

SRCS				=	$(MAIN_SRCS) $(LEXER_SRCS) $(PARSER_SRCS) $(BUILTINS_SRCS) $(EXEC_SRCS) $(STRUCT_UTILS_SRCS) $(TEST_SRCS)
OBJS				=	$(patsubst %.c, $(OBJ_DIR)%.o, $(notdir $(SRCS)));

# path to find .c file

VPATH				=	 $(MAIN_DIR):$(LEXER_DIR):$(PARSER_DIR):$(BUILTINS_DIR):$(EXEC_DIR):$(STRUCT_UTILS_DIR):$(TEST_DIR)

# libft variable

LIBFT_DIR			=	libft/
LIBFT_NAME			=	libft.a
LIBFT_FLAGS			=	-L$(LIBFT_DIR) -lft

# compilation variable

CC					=	gcc
HDRS				=	-Iincludes/.
CFLAGS				=	-Wall -Wextra -Werror
RLFLAGS				=	-L$(HOME)/.brew/opt/readline/lib -lreadline
RM					=	rm -f

# color variable

RED					=	\033[0;31m
GREEN				=	\033[0;32m
YELLOW				=	\033[0;33m
NONE				=	\033[0m

all: $(LIBFT_DIR)$(LIBFT_NAME) $(NAME)

$(NAME): $(OBJS)
	@printf "\n$(GREEN)minishell object created successfully$(NONE)\n"
	@$(CC) $(HDRS) $(CFLAGS) -o $@ $^ $(LIBFT_FLAGS) $(RLFLAGS)
	@printf "$(GREEN)minishell program created successfully$(NONE)\n"

$(LIBFT_DIR)$(LIBFT_NAME):
	@printf "libft: "
	@make -C $(LIBFT_DIR) all
	@printf "\n$(GREEN)libft created successfully$(NONE)\n"
	@printf "minishell object: "

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(HDRS) $(CFLAGS) -c $^ -o $@
	@printf "$(YELLOW).$(NONE)"

clean:
	@make -C $(LIBFT_DIR) clean
	@$(RM) $(OBJS)
	@echo "$(RED)##### Removed minishell object files #####$(NONE)"

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "$(RED)##### Removed minishell executable #####$(NONE)"

re: fclean all

ifeq ($(MAIN), ben)
	$(info compile with MAIN: $(MAIN))
else ifeq ($(MAIN), tom)
	$(info compile with MAIN: $(MAIN))
else
	$(info compile with MAIN: minishell)
endif

.PHONY: all clean fclean re
