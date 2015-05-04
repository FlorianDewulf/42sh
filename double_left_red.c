/*
** write_on_tmp_file.c for 42 in /home/david/Projet/42sh/exec/redir_droite
** 
** Made by david blervaque
** Login   <blerva_d@epitech.net>
** 
** Started on  Wed May  9 10:24:24 2012 david blervaque
** Last update Tue May 22 22:38:26 2012 florian dewulf
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	"42sh.h"

void		write_file(t_dlr *list, int *fd)
{
  char		tmp;

  tmp = '\n';
  xclose(fd[0]);
  while (list->next != NULL)
    {
      write(fd[1], list->line, my_strlen(list->line));
      write(fd[1], &tmp, 1);
      list = list->next;
    }
  exit(1);
}

void		exec_file(char *bin, char **param, t_env *env, int *pfd)
{
  xclose(pfd[1]);
  xdup2(pfd[0], 0);
  execution(bin, param, env);
}
