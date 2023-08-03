NC			= \033[0m
GREEN		= \033[1;32m
RED			= \033[1;31m

NAME		= minishell
OBJ_DIR		= obj
CC			= gcc
RM			= rm -rf
HEADER		= -I headers
CFLAGS		= -Wall -Wextra -Werror
LFLAGS		= -lreadline -lncurses
LIBFT		= Libft/libft.a
GLOBAL		= src/main.c src/exit_expansion.c src/ms_line_executer.c src/utils.c src/ms_line_executer1.c \
			src/ms_line_executer2.c src/utils1.c
COMMANDS	= src/commands/cd.c src/commands/cmd_utils.c src/commands/echo.c src/commands/exit.c \
			src/commands/pwd.c src/commands/env.c src/commands/export.c src/commands/unset.c \
			src/commands/export_utils1.c src/commands/export_utils2.c
TOKENIZER	= src/tokenizer/tk_tokenizer.c src/tokenizer/tk_utils.c src/tokenizer/tk_wordsplit.c \
            src/tokenizer/tk_name_tokens.c src/tokenizer/tk_expander.c src/tokenizer/tk_remove_quotes.c
ENVIRONMENT	= src/environment/ev_init_env.c
LEXER		= src/lexer/lexer.c
EXECUTE		= src/execute/parser.c
FONCTION_A  = src/fonction_aid/concat.c src/fonction_aid/ft_patht.c src/fonction_aid/ft_strjoin_exe.c
G_N_L 		= src/G_N_L/get_next_line.c src/G_N_L/get_next_line_utils.c
HERDOC 		= src/herdoc/creat_linkdlist.c src/herdoc/herd_1.c src/herdoc/herd_2.c
PIPE 		= src/pipe/closer.c src/pipe/exec_pipe.c src/pipe/exec_pipe1.c
REDIR 		= src/redir/child_redir.c src/redir/file_redir.c src/redir/redirect_fd.c
OBJS		= $(GLOBAL:%.c=%.o) \
			$(TOKENIZER:%.c=%.o) \
            $(ENVIRONMENT:%.c=%.o) \
        	$(EXECUTE:%.c=%.o) \
			$(LEXER:%.c=%.o) \
			$(FONCTION_A:%.c=%.o) \
			$(G_N_L:%.c=%.o) \
			$(HERDOC:%.c=%.o) \
			$(PIPE:%.c=%.o) \
			$(REDIR:%.c=%.o) \
			$(COMMANDS:%.c=%.o)

all:
	@$(MAKE) -C Libft --no-print-directory
	@$(MAKE) $(NAME) --no-print-directory

$(NAME): $(OBJS)
	
	@gcc $(CFLAGS) -fsanitize=address -g $(OBJS) $(LIBFT) -o $@ $(LFLAGS)
	@echo "${GREEN} ##### minishell Ready! ##### ${NC}"

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) clean -C Libft --no-print-directory
	@$(RM) $(OBJS)
	@echo "${GREEN} ##### minishell Clean Objects ##### ${NC}"

fclean: clean
	@$(MAKE) fclean -C Libft --no-print-directory
	@$(RM) $(NAME)
	@echo "${GREEN} ##### minishell Removed ##### ${NC}"

re: fclean all

.PHONY: all clean fclean re
