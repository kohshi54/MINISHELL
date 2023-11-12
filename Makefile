NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror 
DEPFLAGS = -MMD -MP -MF $(DEP_DIR)$*.d

SRC_DIR		= src/
OBJ_DIR		= obj/
DEP_DIR		= dep/

SRCS = 	main.c \
		ft_readline.c \
		ft_getenviron.c \
		lexer/lexer.c \
		lexer/lexer_utils.c \
		lexer/lexer_utils2.c \
		parser/parser.c \
		parser/parser_utils.c \
		parser/parser_utils2.c \
		expander/expander.c \
		expander/expander_params.c \
		expander/expander_params_utils.c \
		expander/expander_split.c \
		expander/expander_split_utils.c \
		expander/expander_removal.c \
		expander/expander_removal_utils.c \
		converter/converter.c \
		converter/converter_utils.c \
		executer/pipex.c \
		executer/pipex_utils.c \
		executer/heredoc.c

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:%.c=%.o))
DEPS = $(addprefix $(DEP_DIR), $(SRCS:%.c=%.d))

LIBFT = libft.a
LIBFTDIR = src/libft/

LIBFLAGS = -L./$(LIBFTDIR) -lft -lreadline

INCLUDES = -I./include -I./$(LIBFTDIR)/include
vpath %.c $(SRC_DIR)

all :  $(OBJ_DIR) $(DEP_DIR) $(NAME)

$(OBJ_DIR) $(DEP_DIR) :
	@mkdir -p $@
	@mkdir -p obj/lexer/ obj/parser/ obj/expander/ obj/converter/ obj/executer/

$(OBJ_DIR)%.o: %.c
	$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LIBFLAGS) -o $(NAME)

$(LIBFT) : $(LIBFTDIR)
	$(MAKE) -C $(LIBFTDIR)

clean : 
	rm -rf $(OBJS) $(DEPS) $(DEP_DIR) $(OBJ_DIR)
	rm -rf build

fclean : clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFTDIR)

re : fclean all

-include $(DEPS)

.PHONY : clean fclean re all