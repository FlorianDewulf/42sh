/*
** list_to_tab.c for 42sh in /home/lund/Dossier courant/42sh/func/termcap
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Sat May 12 11:10:50 2012 florian dewulf
** Last update Thu May 17 09:34:26 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

char		**list_to_tab(t_env *env)
{
  int		i;
  t_env		*tmp;
  char		**tab;

  tmp = env;
  while (tmp)
    {
      i++;
      tmp = tmp->next;
    }
  if ((tab = malloc((i + 1) * sizeof(char *))) == NULL)
    return (my_puterror_null(EXIT_MALLOC));
  i = 0;
  tmp = env;
  while (tmp)
    {
      tab[i++] = tmp->line;
      tmp = tmp->next;
    }
  tab[i] = NULL;
  return (tab);
}
