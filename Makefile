NAME = minishell


SRC_MAN = minishell.c get_cmd_file.c utils_main.c ./utils/ft_split.c ./utils/ft_strdup.c ./src/lexer.c ./src/syntax_error.c \
		./utils/ft_bzero.c  ./utils/ft_substr.c ./utils/ft_strjoin.c ./utils/ft_strcmp.c ./utils/ft_utlis_2.c \
		./utils/ft_utils_1.c ./utils/ft_calloc.c ./utils/ft_strlcpy.c  ./utils/ft_itoa.c execution/here_doc.c \
		./utils/ft_strlen.c execution/execution.c utils/ft_strrchr.c utils/ft_strncmp.c builtins/_env.c builtins/_echo.c \
		execution/files_fork.c ./src/second_utils.c execution/exec_child.c execution/exec_builtin.c utils/ft_strchr.c execution/file_builting.c \
		 ./src/expand.c ./src/utils_expand.c ./builtins/exit.c ./builtins/unset.c \
		./builtins/re_export.c ./builtins/cd.c ./builtins/pwd.c execution/paths.c execution/utils_child.c \
		execution/utils_path.c ./builtins/utils_export.c ./src/utils_expand2.c ./src/utils_expand3.c ./src/utils_lexer.c ./src/utils_lexer2.c ./src/utils_lexer3.c ./builtins/msg_valid.c ./src/my_check.c ./execution/dup_built.c ./execution/utils_here_doc.c

CFLAGS =  -lreadline -lcurses -L /Users/ysabr/Desktop/readline-8.2 -I /Users/ysabr/Desktop/readline-8.2 -Wextra -Werror -Wall 

all : $(NAME)
$(NAME) : $(SRC_MAN)
		stty -echoctl
		cc  $(CFLAGS) $(SRC_MAN) -o $(NAME)

clean :
		rm -rf $(OBJS)

fclean : clean
		rm -rf $(NAME)

re : fclean all
