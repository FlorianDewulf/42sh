/*
** check_guillemet.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Fri Apr 20 18:37:50 2012 florian dewulf
** Last update Fri Apr 20 18:47:47 2012 florian dewulf
*/

#include	"42sh.h"

int		check_guillemet(char *str)
{
  int		curs;
  char		c;

  curs = -1;
  while (str[++curs])
    {
      if (str[curs] == '"' || str[curs] == '\'' || str[curs] == '`')
	{
	  c = str[curs];
	  while (str[++curs] && str[curs] != c);
	  if (str[curs] == '\0')
	    return (1);
	}
    }
  return (0);
}
