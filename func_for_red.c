/*
** func_for_red.c for 42 in /home/david/Projet/42sh/exec/redir_droite
** 
** Made by david blervaque
** Login   <blerva_d@epitech.net>
** 
** Started on  Wed May  2 15:34:29 2012 david blervaque
** Last update Tue May 22 14:27:07 2012 florian dewulf
*/

#include	<stdlib.h>
#include	<stdio.h>
#include	<unistd.h>
#include	<string.h>
#include	"42sh.h"

/*
** Simple redir droite
** Double redir droite
** Simple redir gauche
** Double redir gauche
** Spe !
*/

int		init_srr(int fd_red, char *buff, t_env *env, int *pfd)
{
  int		ret;
  char		*bin;
  char		**tab;
  int		fd;
  int		status;

  (void)pfd;
  status = (fd = xopen(cut_file(buff), 0)) ? 0 : 0;
  if (!(bin = malloc_my_bin(buff)) || !(tab = split_tab(bin)))
    return (-1);
  if ((ret = builtin(tab[0], bin, env)) != 1)
    return (ret);
  if (!(bin = cut_bin(bin)) || !(bin = check_access(bin, env)))
    return (-1);
  if ((ret = fork()) == -1)
    return (-1);
  if (ret == 0)
    {
      xdup2(fd, fd_red);
      execution(bin, tab, env);
    }
  else
    status = xwaitpid(ret, status, 0);
  return ((close(fd)) ? status : status);
}

int		init_drr(int fd_red, char *buff, t_env *env, int *pfd)
{
  int		ret;
  char		*bin;
  char		**tab;
  int		fd;
  int		status;

  (void)pfd;
  status = (fd = xopen(cut_file(buff), 1)) ? 0 : 0;
  if (!(bin = malloc_my_bin(buff)) || !(tab = split_tab(bin)))
    return (-1);
  if ((ret = builtin(tab[0], bin, env)) != 1)
    return (ret);
  if (!(bin = cut_bin(bin)) || !(bin = check_access(bin, env)))
    return (-1);
  if ((ret = fork()) == -1)
    return (-1);
  if (ret == 0)
    {
      xdup2(fd, fd_red);
      execution(bin, tab, env);
    }
  else
    status = xwaitpid(ret, status, 0);
  return ((close(fd)) ? status : status);
}

int		init_slr(int fd_red, char *buff, t_env *env, int *pfd)
{
  int		ret;
  char		*bin;
  char		**tab;
  int		fd;
  int		status;

  (void)fd_red;
  (void)pfd;
  status = (fd = xopen(cut_file(buff), 2)) ? 0 : 0;
  if (!(bin = malloc_my_bin(buff)) || !(tab = split_tab(bin)))
    return (-1);
  if ((ret = builtin(tab[0], bin, env)) != 1)
    return (ret);
  if (!(bin = cut_bin(bin)) || !(bin = check_access(bin, env)))
    return (-1);
  if ((ret = fork()) == -1)
    return (-1);
  if (ret == 0)
    {
      xdup2(fd, 0);
      execution(bin, tab, env);
    }
  else
    status = xwaitpid(ret, status, 0);
  return ((close(fd)) ? status : status);
}

static void	reduc_dlr(t_dlr *list_word, char *bin, char **tab, t_env *env)
{
  int		pfd[2];
  int		ret;

  if (pipe(pfd) == -1 || ((ret = fork()) == -1))
    exit(EXIT_FAILURE);
  if (ret != 0)
    write_file(list_word, pfd);
  else
    exec_file(bin, tab, env, pfd);
}

int		init_dlr(int fd_red, char *buff, t_env *env, int *pifd)
{
  int		ret;
  char		*bin;
  char		**tab;
  t_dlr		*list_word;
  int		status;

  (void)(pifd);
  status = (fd_red -= 1) ? 0 : 0;
  if (!(bin = malloc_my_bin(buff)) || !(tab = split_tab(bin)))
    return (-1);
  if ((ret = builtin(tab[0], bin, env)) != 1)
    return (ret);
  if (!(bin = cut_bin(bin)) || !(bin = check_access(bin, env)))
    return (-1);
  if (!(list_word = read_on_zero(cut_file(buff))))
    return (-1);
  if ((ret = fork()) == -1)
    return (-1);
  if (ret == 0)
    reduc_dlr(list_word, bin, tab, env);
  else
    status = xwaitpid(ret, status, 0);
  usleep(4000);
  return (0);
}
