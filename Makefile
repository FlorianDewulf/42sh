##
## Makefile for 42sh in /home/lund/Dossier courant/42sh/func
## 
## Made by florian dewulf
## Login   <dewulf_f@epitech.net>
## 
## Started on  Thu Apr 26 13:21:47 2012 florian dewulf
## Last update Tue May 22 23:01:32 2012 florian dewulf
##

NAME=	42sh

SRC=	add_build_path.c	\
	alias_command.c		\
	builtin.c		\
	check.c 		\
	check_access.c		\
	check_and.c		\
	check_around.c		\
	check_bin.c		\
	check_cd.c		\
	check_env.c		\
	check_fd.c		\
	check_guillemet.c	\
	check_left_redir.c	\
	check_list.c		\
	check_permission.c	\
	check_opening_line.c	\
	check_prio.c		\
	check_redir.c		\
	check_redir2.c		\
	check_valid_redir.c	\
	comp.c			\
	concate.c		\
	convert_to_tab.c	\
	copy_env.c		\
	cut.c			\
	cut_bin.c		\
	cut_chain.c		\
	cut_file.c		\
	cut_ope.c		\
	decoup_tree.c		\
	double_left_red.c	\
	elem_tree.c		\
	epur_str.c		\
	erase_char.c		\
	exec.c			\
	execution.c		\
	func_for_red.c		\
	free.c			\
	free_tab.c		\
	free_tree.c		\
	gen_env.c		\
	gest_list.c		\
	get_next_line.c		\
	get_next_linebis.c	\
	group_redir.c		\
	init_alias.c		\
	init_history.c		\
	init_redir.c		\
	in_order.c		\
	last_check.c		\
	lexer.c			\
	lex_hist.c		\
	limit_history.c		\
	list.c			\
	list_to_tab.c		\
	main.c			\
	match.c			\
	mini_lex.c		\
	modif_buffer_read.c	\
	modif_list.c		\
	move_tree.c		\
	multipipe.c		\
	my_cd.c			\
	my_cd_moins.c		\
	my_cd_point.c		\
	my_getnbr.c		\
	my_main_read.c		\
	my_putchar.c		\
	my_puterror.c		\
	my_putstr.c		\
	my_readline.c		\
	my_revstr.c		\
	my_setenv.c		\
	my_strcpy.c		\
	my_strlen.c		\
	my_tree.c		\
	order_com.c		\
	order_com_bis.c		\
	parse_env.c		\
	parser.c		\
	passif_mode.c		\
	paste_all.c		\
	put_end_word.c		\
	read_on_zero.c		\
	read_simple.c		\
	redir_double.c		\
	redir_pipe.c		\
	reduc_norme.c		\
	replace_string.c	\
	rmbhistory.c		\
	signal_check.c		\
	split.c			\
	suppr_useless.c		\
	take_prompt.c		\
	take_separ.c		\
	tcput_word.c		\
	termcap.c		\
	term_capacity.c		\
	xchdir.c		\
	xfree.c			\
	xfunc.c			\
	xopen.c			\
	xmalloc.c		\
	xwaitpid.c

OBJ=	$(SRC:.c=.o)

CFLAGS=	-W -Wall -ggdb3

all:	$(OBJ)
	cc -o $(NAME) $(OBJ) -ltermcap
	make -C ./echo_dir all
	make -C ./history_dir all

clean:
	rm -f $(OBJ)
	make -C ./echo_dir clean
	make -C ./history_dir clean

fclean:	clean
	rm -f $(NAME)
	make -C ./echo_dir fclean
	make -C ./history_dir fclean

re:	fclean all
	rm -f $(OBJ)
	make -C ./echo_dir re
	make -C ./history_dir re