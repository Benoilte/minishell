# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 11:59:35 by bebrandt          #+#    #+#              #
#    Updated: 2024/07/09 11:44:22 by bebrandt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell

MAIN				=
LEXER				=	set
PARSER				=	set
BUILTINS			=	set
EXEC				=	set
STRUCT_UTILS		=	set
TEST				=	set
SRCS_DIR			=	srcs/
OBJ_DIR				=	objs/

# main ressources

MAIN_DIR			=	$(SRCS_DIR)main/

ifeq ($(MAIN), debug)
	MAIN_SRCS		+=	$(addprefix $(MAIN_DIR), $(addsuffix .c, main_debug))
	DEBUG_FLAG		= -g
else
	MAIN_SRCS		+=	$(addprefix $(MAIN_DIR), $(addsuffix .c, minishell))
endif

MAIN_SRCS			+=	$(addprefix $(MAIN_DIR), $(addsuffix .c, interactive_minishell \
						non_interactive_minishell minishell_utils signal))

# lexer ressources

ifeq ($(LEXER), set)
	LEXER_DIR			=	$(SRCS_DIR)lexer/
	LEXER_SRCS			=	$(addprefix $(LEXER_DIR), $(addsuffix .c, lexer lexer_action_utils \
							lexer_get_data lexer_define_type))
endif

# parser ressources

ifeq ($(PARSER), set)
	PARSER_DIR			=	$(SRCS_DIR)parser/
	PARSER_SRCS			=	$(addprefix $(PARSER_DIR), $(addsuffix .c, parser parser_utils \
							parser_check_redirections parser_check_cmd parser_update_data \
							parser_update_data_utils parser_update_expansion))
endif

# builtins ressources

ifeq ($(BUILTINS), set)
	BUILTINS_DIR		=	$(SRCS_DIR)builtins/
	BUILTINS_SRCS		=	$(addprefix $(BUILTINS_DIR), $(addsuffix .c, builtins pwd utils_builtins \
							cd env ft_env_utils echo export unset exit))
endif

# exec ressources

ifeq ($(EXEC), set)
	EXEC_DIR			=	$(SRCS_DIR)exec/
	EXEC_SRCS			=	$(addprefix $(EXEC_DIR), $(addsuffix .c, exec sort_red \
							ft_cmd process red sort_cmd_builtin utils_exec exec_commands \
							file_desriptors_utils handle_execution_error))
endif

# struct_utils ressources

ifeq ($(STRUCT_UTILS), set)
	STRUCT_UTILS_DIR	=	$(SRCS_DIR)struct_utils/
	STRUCT_UTILS_SRCS	=	$(addprefix $(STRUCT_UTILS_DIR), $(addsuffix .c, init new add_back \
							last size clean_bash clear_all env_utils ms_env_utils bash_utils))
endif

# test ressources

ifeq ($(TEST), set)
	TEST_DIR			=	$(SRCS_DIR)test/
	TEST_SRCS			=	$(addprefix $(TEST_DIR), $(addsuffix .c, test test_utils))
endif

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
CFLAGS				=	-Wall -Wextra -Werror $(DEBUG_FLAG)
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
	@$(CC) $(CFLAGS) $(HDRS) -o $@ $^ $(LIBFT_FLAGS) $(RLFLAGS) $(DEBUG_FLAG)
	@printf "$(GREEN)minishell program created successfully$(NONE)\n"

$(LIBFT_DIR)$(LIBFT_NAME):
	@printf "libft: "
	@make -C $(LIBFT_DIR) all
	@printf "\n$(GREEN)libft created successfully$(NONE)\n"
	@printf "minishell object: "

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(HDRS) -c $^ -o $@ $(DEBUG_FLAG)
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

.PHONY: all clean fclean re
