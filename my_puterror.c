/*
** my_puterror.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Fri Apr 20 18:36:53 2012 florian dewulf
** Last update Sat May 19 01:12:22 2012 kevin lansel
*/

#include	<unistd.h>
#include	"42sh.h"

void		*my_puterror_null(char *str)
{
  write(2, str, my_strlen(str));
  return (NULL);
}

int		my_puterror_int(char *str)
{
  write(2, str, my_strlen(str));
  return (-1);
}
