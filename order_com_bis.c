/*
** order_com_bis.c for 42sh in /home/lund/svn/Correction/patch
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Tue May 22 22:59:12 2012 florian dewulf
** Last update Tue May 22 23:00:51 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

char		*order_com_bis(int *i, int tmp, char *com)
{
  int		memo;

  if (*i == 0)
    {
      if ((memo = func(com, i, tmp - 1)) == 0)
	return (NULL);
      return (cut_com(com, i, tmp, memo));
    }
  else if (com[*i] == '|' || com[*i] == ';' || com[*i] == '&')
    {
      (*i)++;
      if ((memo = func(com, i, tmp)) == 0)
	  return (NULL);
      return (cut_com(com, i, tmp + 1, memo));
    }
  else
    {
      (*i) = tmp + 1;
      while (com[*i] && ((com[*i] >= '0' && com[*i] <= '9') || com[*i] == '<'
			 || com[*i] == '>'))
	(*i)++;
    }
  return (com);
}
