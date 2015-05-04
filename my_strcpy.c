/*
** my_strcpy.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Fri Apr 20 16:51:49 2012 florian dewulf
** Last update Sat May 12 18:17:57 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

char		*my_strcpy(char *str)
{
  char		*dest;
  int		curs;

  curs = -1;
  if (str == NULL)
    return (NULL);
  dest = malloc((my_strlen(str) + 1) * sizeof(char));
  if (dest == NULL)
    return (NULL);
  while (str[++curs])
    dest[curs] = str[curs];
  dest[curs] = '\0';
  return (dest);
}
