/*
** xmalloc.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Fri Apr 20 18:14:22 2012 florian dewulf
** Last update Wed May 16 11:13:06 2012 kevin lansel
*/

#include	<stdlib.h>
#include	"42sh.h"

void		*xmalloc(int size)
{
  void		*ptr;

  ptr = malloc(size);
  if (ptr == NULL)
    return (my_puterror_null(EXIT_MALLOC));
  return (ptr);
}
