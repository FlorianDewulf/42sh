/*
** check_and.c for 42sh.h in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Thu Apr 26 11:25:03 2012 florian dewulf
** Last update Wed May  2 11:37:58 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

char		*check_and(int tmp, int *cur, char *str)
{
  if (str[*cur + 1] == '&')
    {
      if (str[*cur + 2] != '<' && str[*cur + 2] != '>' &&
	  str[*cur + 2] != '|' &&
	  str[*cur + 2] != ';' && str[*cur + 2] != '&')
	return (cut_chain(tmp, *cur, str));
      return (NULL);
    }
  else if (str[*cur + 1] == '>')
    {
      if (str[*cur + 2] == '>')
	{
	  if (str[*cur + 3] == '<' || str[*cur + 3] == '>' ||
	      str[*cur + 3] == ';' || str[*cur + 3] == '|' ||
	      str[*cur + 3] == '&')
	    return (0);
	  return (cut_chain(tmp, *cur, str));
	}
      else if (str[*cur + 2] != '<' && str[*cur + 2] != '|' &&
	       str[*cur + 2] != ';' && str[*cur + 2] != '&')
	return (cut_chain(tmp, *cur, str));
      return (NULL);
    }
  else
    return (NULL);
}
