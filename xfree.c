/*
** xfree.c for 42sh in /home/lund/Dossier courant/42sh/func/termcap
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Sat May 12 17:58:47 2012 florian dewulf
** Last update Sat May 12 18:00:57 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

void		*xfree(void *ptr)
{
  if (ptr != NULL)
    {
      free(ptr);
      ptr = NULL;
    }
  return (ptr);
}
