/*
** my_putstr.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Fri Apr 20 18:48:03 2012 florian dewulf
** Last update Thu May 10 23:32:00 2012 florian dewulf
*/

#include	<unistd.h>
#include	"42sh.h"

void		my_putstr(char *str)
{
  if (str != NULL)
    write(1, str, my_strlen(str));
}
