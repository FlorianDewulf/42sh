/*
** redir_pipe.c for 42sh in /home/lund/Dossier courant/42sh/v1.0
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Thu May 17 10:37:31 2012 florian dewulf
** Last update Sat May 19 17:37:42 2012 kevin lansel
*/

#include	"42sh.h"

int		init_srr2(int fd_red, char *buff, t_env *env, int *pfd)
{
  char		*bin;
  char		**tab;
  int		fd;

  (void)fd_red;
  fd = xopen(cut_file(buff), 0);
  if (!(bin = malloc_my_bin(buff)) || !(tab = split_tab(bin)))
    return (-1);
  if (!(bin = cut_bin(bin)) || !(bin = check_access(bin, env)))
    return (-1);
  if (comp(tab[0], "exit"))
    return (-2);
  if (comp(tab[0], "false"))
    return (0);
  xclose(pfd[1]);
  xdup2(pfd[0], 0);
  xdup2(fd, 1);
  execution(bin, tab, env);
  return (0);
}

int		init_drr2(int fd_red, char *buff, t_env *env, int *pfd)
{
  char		*bin;
  char		**tab;
  int		fd;

  (void)fd_red;
  fd = xopen(cut_file(buff), 1);
  if (!(bin = malloc_my_bin(buff)) || !(tab = split_tab(bin)))
    return (-1);
  if (!(bin = cut_bin(bin)) || !(bin = check_access(bin, env)))
    return (-1);
  if (comp(tab[0], "exit"))
    return (-2);
  if (comp(tab[0], "false"))
    return (0);
  xclose(pfd[1]);
  xdup2(pfd[0], 0);
  xdup2(fd, 1);
  execution(bin, tab, env);
  return (0);
}

int		redir_pipe(char *str, t_env *env, int *fd)
{
  t_redir	*red;
  char		*ope_tmp;
  int		i;
  int		curs;
  int		fd_red;

  i = 0;
  curs = 0;
  red = init_redir_2();
  ope_tmp = cut_ope(str);
  while (i < SIZE_REDIR)
    {
      if (match_fdred(ope_tmp, red[curs].redir) == 1)
	i = SIZE_REDIR;
      else
	{
	  curs++;
	  i++;
	}
    }
  fd_red = calc_fd(ope_tmp);
  if (curs != SIZE_REDIR)
    return (red[curs].func(fd_red, str, env, fd));
  return (-1);
}
