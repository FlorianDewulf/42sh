/*
** redir_double.c for 42sh.h in /home/lund/svn/Correction
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Tue May 22 00:01:00 2012 florian dewulf
** Last update Tue May 22 22:57:34 2012 florian dewulf
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	"42sh.h"

static void	open_the_files(int *pfd, char **tab)
{
  in_order(tab);
  if (comp(tab[1], "<"))
    pfd[0] = xopen(tab[2], 2);
  else
    pfd[0] = -2;
  if (match_fdred(tab[3], "*>>"))
    pfd[1] = xopen(tab[4], 1);
  else
    pfd[1] = xopen(tab[4], 0);
}

static void	left_redir_double(char *str, int fd, char *name, t_env *env)
{
  t_dlr		*list_word;
  int		pfd[2];
  int		ret;
  t_env		*tmp;

  tmp = env;
  if (!(list_word = read_on_zero(name)))
    exit(EXIT_FAILURE);
  if ((str = check_access(str, tmp)) == NULL || pipe(pfd) == -1 ||
      ((ret = fork()) == -1))
    exit(EXIT_FAILURE);
  if (ret != 0)
    write_file(list_word, pfd);
  else
    {
      xclose(pfd[1]);
      xdup2(fd, 1);
      xdup2(pfd[0], 0);
      execution(str, split_tab(str), env);
    }
  exit(EXIT_SUCCESS);
}

static void	exe_redir(char *str, t_env *env)
{
  char		**tabv;
  int		pid;
  char		*tmp;
  t_env		*tmp_env;

  tmp_env = env;
  tabv = split_tab(str);
  tmp = tabv[0];
  if ((pid = builtin(tabv[0], str, env)) != 1)
    exit(EXIT_SUCCESS);
  if ((tmp = check_access(tmp, tmp_env)) == NULL)
    exit(EXIT_FAILURE);
  tmp_env = env;
  execution(tmp, tabv, tmp_env);
}

int		redir_double(char *buff, t_env *env)
{
  int		pfd[2];
  int		ret;
  char		**tab;
  int		status;

  status = 0;
  if ((ret = fork()) == -1)
    return (-1);
  tab = mini_lex(buff);
  if (ret == 0)
    {
      open_the_files(pfd, tab);
      if (pfd[0] == -2)
	left_redir_double(tab[0], pfd[1], tab[2], env);
      else
	{
	  xdup2(pfd[1], 1);
	  xdup2(pfd[0], 0);
	  exe_redir(tab[0], env);
	}
    }
  else
    status = xwaitpid(ret, status, 0);
  return (status);
}
