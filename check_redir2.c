/*
** check_redir.c for 42 in /home/david/Projet/42sh/exec/redir_droite
** 
** Made by david blervaque
** Login   <blerva_d@epitech.net>
** 
** Started on  Wed May  2 15:45:14 2012 david blervaque
** Last update Tue May 22 12:41:52 2012 florian dewulf
*/

#include	"42sh.h"

int		check_redir2(char *buff, t_env *env, int *fd)
{
  t_redir	*red;
  char		*ope_tmp;
  int		i;
  int		curs;
  int		fd_red;

  i = (curs = 0) ? 0 : 0;
  if (valid_redir(buff) == 1)
    return (redir_double(buff, env));
  red = init_redir();
  ope_tmp = cut_ope(buff);
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
    red[curs].func(fd_red, buff, env, fd);
  return (0);
}
