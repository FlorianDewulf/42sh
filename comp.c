/*
** comp.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Sat Apr 21 15:17:30 2012 florian dewulf
** Last update Sun May 13 23:25:07 2012 florian dewulf
*/

#include	<string.h>
#include	"42sh.h"

int		comp(char *str, char *pattern)
{
  int		curs;

  curs = -1;
  if (str == NULL || pattern == NULL)
    return (0);
  if (strlen(str) != strlen(pattern))
    return (0);
  while (str[++curs] && pattern[curs])
    if (str[curs] != pattern[curs])
      return (0);
  if (!str[curs] && !pattern[curs])
    return (1);
  return (0);
}
