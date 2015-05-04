/*
** put_end_word.c for 42sh in /home/lund/Dossier courant/42sh/func/termcap
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Thu May 10 09:26:11 2012 florian dewulf
** Last update Wed May 16 17:52:34 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

void		put_end_word(int *curs, char *buffer)
{
  int		nb;

  nb = curs[0];
  while (buffer[nb])
    my_putchar(buffer[nb++]);
  xfree(curs);
  my_putchar('\n');
}
