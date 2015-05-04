/*
** free_tab.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Sat Apr 21 15:30:31 2012 florian dewulf
** Last update Wed May 16 17:49:02 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

int		free_tab(char **tab)
{
  int		curs;

  curs = -1;
  while (tab[++curs])
    xfree(tab[curs]);
  xfree(tab);
  return (0);
}
