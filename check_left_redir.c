/*
** check_left_redir.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Wed Apr 25 16:48:45 2012 florian dewulf
** Last update Fri Apr 27 12:04:34 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

char		*check_left_redir(char *str, int tmp, int *cur)
{
  if (str[*cur + 1] == '<' &&
      (str[*cur + 2] != '|' && str[*cur + 2] != '<' && str[*cur + 2] != ';' &&
       str[*cur + 2] != '>' && str[*cur + 2] && str[*cur + 2] != '&'))
    return (cut_chain(tmp, *cur, str));
  else if (str[*cur + 1] == '<')
    return (NULL);
  else if ((str[*cur + 1] != '|' && str[*cur + 1] != '<' &&
	    str[*cur + 1] != ';' &&
	    str[*cur + 1] != '>' && str[*cur + 1] && str[*cur + 1] != '&'))
    return (cut_chain(tmp, *cur, str));
  else
    return (NULL);
}
