/*
** check_around.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Thu Apr 26 10:03:17 2012 florian dewulf
** Last update Fri Apr 27 12:02:07 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

char		*check_around(int tmp, int cur, char *str, char c)
{
  if (c == '|' && str[cur + 1] == '|' &&
      (str[cur + 2] == '>' || str[cur + 2] == '<' || str[cur + 2] == ';' ||
       str[cur + 2] == '&' || !str[cur + 2]))
    return (NULL);
  else if (c == '|' && str[cur + 1] != '>' && str[cur + 1] != '<' &&
	   str[cur + 1] != ';' && str[cur + 1] != '&' &&
	   str[cur - 1] != '>' && str[cur - 1] != '<' &&
	   str[cur - 1] != ';' && str[cur - 1] != '&')
    return (cut_chain(tmp, cur, str));
  else if (c == ';' && str[cur + 1] != '>' && str[cur + 1] != '<' &&
	   str[cur + 1] != ';' && str[cur + 1] != '&' &&
	   str[cur + 1] != '|' && str[cur - 1] != '>' && str[cur - 1] != '<' &&
	   str[cur - 1] != ';' && str[cur - 1] != '&')
    return (cut_chain(tmp, cur, str));
  return (NULL);
}
