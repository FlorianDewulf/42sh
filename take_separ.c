/*
** take_separ.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Wed Apr 25 18:16:45 2012 florian dewulf
** Last update Wed May  2 11:46:19 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

char		*take_separ(char *str, int *curs)
{
  int		tmp;

  tmp = *curs;
  if (!str[tmp])
    return (NULL);
  while (str[(*curs)] != '|' && str[(*curs)] != '&' &&
	 str[(*curs)] != '>' && str[(*curs)] != '<' &&
	 str[(*curs)] != ';' && str[(*curs)])
    (*curs)++;
  if (str[*curs] == '&' && str[*curs + 1] == '>' && str[*curs + 2] == '>')
    (*curs) += 3;
  else if (str[*curs + 1] == str[*curs] || (str[*curs] == '&' &&
				       str[*curs + 1] == '>'))
    (*curs) += 2;
  else if (str[*curs] == '>' && str[*curs + 1] == '&')
    {
      while (str[*curs] != ' ' && str[*curs] != '\t' && str[*curs])
	(*curs)++;
    }
  else
    (*curs)++;
  return (cut_chain(tmp, *curs, str));
}
