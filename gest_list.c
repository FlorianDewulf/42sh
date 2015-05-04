/*
** gest_list.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Sat Apr 21 15:32:46 2012 florian dewulf
** Last update Fri May 18 17:21:34 2012 kevin lansel
*/

#include	<stdlib.h>
#include	"42sh.h"

int		add_to_list(t_env **env, char *str)
{
  t_env		*elem;
  t_env		*tmp;

  tmp = *env;
  elem = malloc(sizeof(t_env));
  if (elem == NULL)
    return (my_puterror_int(EXIT_MALLOC));
  elem->previous = NULL;
  elem->next = NULL;
  elem->line = my_strcpy(str);
  if (tmp == NULL)
    *env = elem;
  else
    {
      while (tmp->next != NULL)
	tmp = tmp->next;
      tmp->next = elem;
      elem->previous = tmp;
    }
  return (1);
}

void		create_list(t_env **env, char **tab_env)
{
  int		curs;
  t_env		*tmp_env;

  *env = NULL;
  tmp_env = *env;
  curs = -1;
  while (tab_env[++curs])
    add_to_list(&tmp_env, tab_env[curs]);
  free_tab(tab_env);
  *env = tmp_env;
}
