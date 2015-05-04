/*
** check_fd.c for 42 in /home/david/Projet/42sh/exec/redir_droite
** 
** Made by david blervaque
** Login   <blerva_d@epitech.net>
** 
** Started on  Mon Apr 30 17:07:00 2012 david blervaque
** Last update Wed May 16 19:21:16 2012 florian dewulf
*/

#include	"42sh.h"

int		calc_fd(char *str)
{
  int		curs;
  char		*tmp;
  int		fd;

  curs = -1;
  while (str[++curs] && str[curs] != '<' && str[curs] != '&');
  if (str[curs] != '\0' && str[curs] != '&' && curs > 0 && str[curs - 1] != '>')
    return (-1);
  curs = -1;
  while (str[++curs] && str[curs] != '>');
  if (str[curs] == '\0' || curs == 0)
    return (1);
  tmp = cut_chain(0, curs, str);
  fd = my_getnbr(tmp);
  xfree(tmp);
  return (fd);
}
