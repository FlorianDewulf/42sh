/*
** match.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Tue May  1 23:01:54 2012 florian dewulf
** Last update Thu May 17 10:28:58 2012 florian dewulf
*/

#include	"42sh.h"

int		match_fdred(char *str, char *pattern)
{
  int		curs1;
  int		curs2;

  curs1 = 0;
  curs2 = 0;
  while (str[curs1] && pattern[curs2])
    {
      if (pattern[curs2] == '*')
	{
	  while (str[curs1] <= '9' && str[curs1] >= '0')
	    curs1++;
	  curs2++;
	}
      else if (str[curs1] != pattern[curs2])
	return (0);
      else
	{
	  curs1++;
	  curs2++;
	}
    }
  if (!str[curs1] && !pattern[curs2])
    return (1);
  return (0);
}
