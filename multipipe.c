/*
** multipipe.c for 42sh in /home/lund/Dossier courant/42sh/func/termcap/arbre/toast
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Mon May 14 22:01:28 2012 florian dewulf
** Last update Sun May 20 18:58:15 2012 florian dewulf
*/

#include	<unistd.h>
#include	<sys/wait.h>
#include	<stdlib.h>
#include	"42sh.h"

static void	wait_read(t_tree *ptr, t_env *env, int *fd, int where_write)
{
  char		*str;
  char		**tab;

  if (ptr && ptr->type == REDIR)
    redir_pipe(ptr->exp, env, fd);
  else
    {
      tab = split_tab(ptr->exp);
      if (tab == NULL || (tab && tab[0] == NULL))
	exit(EXIT_FAILURE);
      builtin_pipe(tab[0], env, fd);
      if ((str = check_access(tab[0], env)) == NULL)
	exit(EXIT_FAILURE);
      xclose(fd[1]);
      xdup2(fd[0], 0);
      xdup2(where_write, 1);
      execution(str, tab, env);
      exit(EXIT_FAILURE);
    }
}


static int	cut_him(t_tree *ptr, t_env *env, int *pfd, int where_write)
{
  char		**tab;
  char		*str;

  if (ptr->right->type == REDIR)
    return (redir_pipe(ptr->right->exp, env, pfd));
  tab = split_tab(ptr->right->exp);
  if (tab == NULL || (tab && tab[0] == NULL))
    exit(EXIT_FAILURE);
  builtin_pipe(tab[0], env, pfd);
  if ((str = check_access(tab[0], env)) == NULL)
    exit(EXIT_FAILURE);
  xclose(pfd[1]);
  xdup2(pfd[0], 0);
  if (where_write != 1)
    xdup2(where_write, 1);
  if (where_write != 1)
    xclose(where_write);
  execution(str, tab, env);
  exit(EXIT_FAILURE);
}

static int	finish_him(t_tree *ptr, t_env *env, int *pfd, int where_write)
{
  int		pid;
  char		*str;
  char		**tab;

  if ((pid = fork()) == -1)
    return (-1);
  if (pid == 0)
    {
      tab = split_tab(ptr->left->exp);
      if (tab == NULL || (tab && tab[0] == NULL))
	exit(EXIT_FAILURE);
      builtin_pipe(tab[0], env, pfd);
      if ((str = check_access(tab[0], env)) == NULL)
	exit(EXIT_FAILURE);
      xclose(pfd[0]);
      xdup2(pfd[1], 1);
      if (where_write != 1)
	xclose(where_write);
      execution(str, tab, env);
      exit(EXIT_FAILURE);
    }
  else
    return (cut_him(ptr, env, pfd, where_write));
}

static int	multi(t_tree *ptr, t_env *env, int where_write)
{
  int		pfd[2];
  int		pid;

  if (pipe(pfd) == -1)
    return (-2);
  if (ptr->left->type == PIPE)
    {
      if ((pid = fork()) == -1)
	return (-2);
      if (pid != 0)
	wait_read(ptr->right, env, pfd, where_write);
      else
	{
	  where_write = pfd[1];
	  return (multi(ptr->left, env, where_write));
	}
    }
  else if (ptr->left->type == COM)
    return (finish_him(ptr, env, pfd, where_write));
  return (-1);
}

int		multipipe(t_tree *ptr, t_env *env)
{
  int		pid;
  int		status;

  status = 0;
  if ((pid = fork()) == -1)
    return (-1);
  if (pid == 0)
    return (multi(ptr, env, 1));
  xwaitpid(pid, status, 0);
  usleep(4000);
  return (0);
}
