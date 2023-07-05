NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

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
		expander/expander_removal_utils.c

OBJS = $(SRCS:%.c=%.o)

LIBFT = LIBFT/libft.a
LIBFTDIR = LIBFT/

INCLUDES = minishell.h

LIBFLAGS = -L./$(LIBFTDIR) -lft -lreadline

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT) minishell.h
	$(CC) $(CFLAGS) $(OBJS) $(LIBFLAGS) -o $(NAME)

$(LIBFT) : $(LIBFTDIR)
	$(MAKE) -C $(LIBFTDIR)

clean :
	rm -f $(OBJS)
	$(MAKE) clean -C $(LIBFTDIR)

fclean : clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFTDIR)

re : fclean all

.PHONY : clean fclean re all