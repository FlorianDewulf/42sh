/*
** cut_chain.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Tue Apr 24 17:18:24 2012 florian dewulf
** Last update Tue May 15 18:54:23 2012 florian dewulf
*/

#include	"42sh.h"

char		*cut_chain(int begin, int end, char *str)
{
  char		*dest;
  int		curs;

  curs = 0;
  dest = xmalloc((end - begin + 1) * sizeof(char));
  while (begin < end)
    dest[curs++] = str[begin++];
  dest[curs] = '\0';
  return (dest);
}
