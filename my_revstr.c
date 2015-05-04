/*
** my_revstr.c for 42sh.h in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Thu May  3 13:12:06 2012 florian dewulf
** Last update Thu May  3 13:15:42 2012 florian dewulf
*/

#include	"42sh.h"

char		*my_revstr(char *str)
{
  int		curs;
  int		end;
  char		tmp;

  end = my_strlen(str) - 1;
  curs = 0;
  while (curs < end)
    {
      tmp = str[end];
      str[end] = str[curs];
      str[curs] = tmp;
      curs++;
      end--;
    }
  return (str);
}
