/*
** 42sh.h for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Fri Apr 20 18:34:22 2012 florian dewulf
** Last update Tue May 22 23:05:05 2012 florian dewulf
*/

#ifndef				__42SH_H__
#define				__42SH_H__

/*
** -----------------------------MACRO--------------------------------------
*/

#define				PATH			"PATH="

#define				PATHBIN			"/bin"
#define				PATHUBIN		"/usr/bin"
#define				PATHSBIN		"/sbin"
#define				PATHUSBIN		"/usr/sbin"
#define				PATHULOCBIN		"/usr/local/bin"
#define				PATHULOCSBIN		"/usr/local/sbin"
#define				OLDPWD_DEFAULT		"OLDPWD=/"

#define				ENV_USER		"USER="
#define				ENV_HOME		"HOME="
#define				ENV_PWD			"PWD="
#define				ENV_TERM		"TERM=xterm"

#define				EXIT_GETCWD		"Can't perform getcwd necessary to generate an env\n"
#define				EXIT_MALLOC		"Can't perform malloc\n"
#define				EXIT_READ		"Invalid read\n"
#define				EXIT_GETPWUID		"Can't perform getpwuid necessary to generate an env\n"
#define				NO_DIR			"The file is not a directory\n"
#define				FILE_WRONG		"File doesn't exist\n"
#define				NO_FILE			"Command not found\n"
#define				FAIL_PERMI		"Permission denied\n"
#define				EXIT_MISS_HOME		"$HOME is missing in env', sorry\n"
#define				EXIT_MISS_PWD		"$PWD is missing in env', sorry\n"
#define				EXIT_MISS_OLDPWD	"$OLDPWD is missing in env', sorry\n"
#define				EXIT_CHDIR		"Change directory fail\n"
#define				EXIT_STAT		"Change directory fail\n"

#define				UP_TOUCH		"[A"
#define				DOWN_TOUCH		"[B"
#define				RIGHT_TOUCH		"[C"
#define				LEFT_TOUCH		"[D"

#define				BUFFER			4096
#define				SIZE_REDIR		4

/*
** -----------------------------STRUCT-------------------------------------
*/

struct				s_env
{
  char				*line;
  struct s_env			*next;
  struct s_env			*previous;
};

struct				s_tree
{
  int				type;
  int				prio;
  char				*exp;
  struct s_tree			*left;
  struct s_tree			*right;
  struct s_tree			*prev;
};

struct				s_alias
{
  char				*pattern;
  char				*exp;
  struct s_alias		*next;
};

struct				s_history
{
  char				*line;
  struct s_history		*next;
  struct s_history		*prev;
};

struct				s_list
{
  struct s_tree			*part;
  struct s_list			*next;
  struct s_list			*prev;
};

struct				s_redir
{
  char				*redir;
  int				(*func)(int, char *, struct s_env *, int *);
};

struct				s_dlr
{
  char				*line;
  struct s_dlr			*next;
};

typedef	struct s_dlr		t_dlr;
typedef struct s_env		t_env;
typedef struct s_tree		t_tree;
typedef struct s_alias		t_alias;
typedef struct s_history	t_history;
typedef struct s_list		t_list;
typedef struct s_redir		t_redir;


/*
** -----------------------------GLOBALE------------------------------------
*/

char				*g_prompt;
int				*g_cursor;
char				*g_buffer;
int				g_exit;
t_history			*g_histo;
t_alias				*g_alias;

/*
** -----------------------------ENUM---------------------------------------
*/


enum				type {
  START = -1,
  PT,
  AND,
  OR,
  PIPE,
  REDIR,
  COM,
  END
};

/*
** -----------------------------PROTOTYPE----------------------------------
*/

int				add_to_list(t_env **, char *);
char				*check_and(int, int *, char *);
char				*check_around(int, int, char *, char);
int				check_guillemet(char *);
char				*check_left_redit(char *, int, int *);
char				*take_command();
char				*check_left_redir(char *, int, int *);
char				*check_redir(char *, int *, int);
int				comp(char *, char *);
int				compegal(char *, char *);
char				*concate(char *, char *);
char				**copy_env(char **);
t_tree				*line_to_list(char *);
char				*cut_chain(int, int, char *);
char				*epur_space(char *);
int				free_tab(char **);
char				*gen_path();
t_env				*gen_env();
void				create_list(t_env **, char **);
void				add_elem(t_tree **, char *);
void				my_puterror(char *);
void				my_putstr(char *);
char				*my_strcpy(char *);
int				my_strlen(char *);
t_env				*parse_env(char **);
char				**split_tab(char *);
char				*take_separ(char *, int *);
void				*xmalloc(int);
char				*my_revstr(char *);
int				check_type(char *);
int				check_env(t_env **);
int				init_termcap(t_env *);
int				check_list(t_tree **);
int				match_fdred(char *, char *);
char				*my_read();
void				my_putchar(char);
char				*xtgetstr_exe(char *, char *);
void				tcput_word(char *, int);
void				erase_char(int *, char *);
void				take_prompt(t_env *);
void				insere_char(char *, int *, char);
void				go_to_left(int *);
void				go_to_right(int *);
t_history			*check_commande(char *, int *, char *, t_history **);
char				*get_next_line(int);
char				*get_next_line_bis(int);
void				init_alias(t_alias **, t_env *);
int				init_history(t_history **, t_env *);
t_history			*modif_buff_read_up(char *, t_history **, int *);
t_history			*modif_buff_read_down(char *, t_history **, int *);
void				add_to_history(t_history **, char *, int);
t_tree				*end_list(t_tree **);
int				check_list_prio(t_tree **);
void				check_first_prio(t_tree**);
void				check_right(t_tree **, int);
void				check_left(t_tree **, int);
t_tree				*my_tree(t_tree *);
void				recurse_tree(t_tree *, t_tree *, int);
t_tree				*init_new_elem(t_tree *);
void				add_to_right(t_tree **, t_tree *);
void				add_to_left(t_tree **, t_tree *);
int				group_redir(t_tree *);
void				put_caractere(int *, char *, char);
void				put_end_word(int *, char *);
void				catch_ctrlz(int);
void				catch_ctrlc(int);
int				termcap_desinit(t_env *);
void				free_env(t_env *);
void				free_history(t_history *);
void				free_alias(t_alias *);
char				*read_simple(char *);
void				*xfree(void *);
char				*paste_all(char **);
char				*replace_string(t_alias *, char *, t_env *);
char				*decoup_from_egal(char *);
void				xclose(int);
void				xdup2(int, int);
int				lexer(char *, t_env *, t_alias *);
char				*check_access(char *, t_env *);
char				**convert_to_tab(t_env *);
int				exec(t_tree **, t_env *);
int				my_getnbr(char *);
int				exe_simple(char *, t_env *);
void				execution(char *, char **, t_env *);
int				browse_pipe_tree(t_tree *, t_tree *, t_env *);
int				last_check(t_tree *);
t_list				*decoup_tree(t_tree *);
int				move_hard_tree_left(t_tree *, t_env *);
int				move_hard_tree_right(t_tree *, t_env *);
int				parser(t_list *, t_env *);
int				init_srr2(int, char *, t_env *, int *);
int				init_drr2(int, char *, t_env *, int *);
int				init_srr(int, char *, t_env *, int *);
int				init_drr(int, char *, t_env *, int *);
int				init_slr(int, char *, t_env *, int *);
int				init_dlr(int, char *, t_env *, int *);
int				init_spe(int, char *, t_env *, int *);
char				*cut_file(char *);
char				*cut_chain(int, int, char *);
char				*check_bin(char *);
char				*malloc_my_bin(char *);
char				*cut_bin(char *);
t_dlr				*fill_list(t_dlr *, char *);
t_dlr				*read_on_zero(char *);
void				write_file(t_dlr *, int *);
void				exec_file(char *, char **, t_env *, int *);
int				calc_fd(char *);
void				*my_puterror_null(char *);
int				my_puterror_int(char *);
int				multipipe(t_tree *, t_env *);
t_redir				*init_redir();
t_redir				*init_redir_2();
int				check_redir2(char *, t_env *, int *);
int				xwaitpid(int, int, int);
char				*cut_ope(char *);
int				xopen(char *, int);
void				free_list(t_tree *);
void				modif_list(t_tree **);
int				redir_pipe(char *, t_env *, int *);
int				check_tab(char **, t_env *);
char				**replace_slash(char *);
int				my_cd_point(t_env *);
int				my_cd_moin(t_env *);
int				old_to_pwd(char *, t_env *);
int				my_cd(int, char **, t_env *);
int				builtin(char *, char *, t_env *);
void				builtin_pipe(char *, t_env *, int *);
void				free_tree(t_tree *);
char				**concate_loop_access(char **, char **, char *);
int				check_permission(char *);
t_env				*suppr_useless(t_env **);
int				my_env(char *, t_env *);
int				xchdir(char *);
int				alias_command(char *, t_alias **, t_env *);
char				*lex_hist(char *, t_history *);
char				*rmbhistory(char *, t_history **);
t_history			*limit_history(t_history *, char *, int, t_env *);
char				**convert_to_tab_history(t_history *);
int				check_arg_passif(char *, t_env *);
void				add_build_path(t_env **);
int				check_arg(t_env *);
char				**mini_lex(char *);
int				valid_redir(char *);
int				check_valid_redir(t_tree *);
int				in_order(char **);
char				*order_com(char *);
int				redir_double(char *, t_env *);
int				func(char *, int *, int);
char				*cut_com(char *, int *, int, int);
char				*order_com_bis(int *, int, char *);

#endif
