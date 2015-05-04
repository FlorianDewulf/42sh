/*
** suppr_useless.c for 42sh in /home/peelou/Documents/Projets/42sh/toast/42sh-2016-dewulf_f
** 
** Made by gery baudry
** Login   <baudry_g@epitech.net>
** 
** Started on  Fri May 18 16:49:06 2012 gery baudry
** Last update Fri May 18 17:35:00 2012 gery baudry
*/

#include	<stdlib.h>
#include	"42sh.h"

t_env		*suppr_useless(t_env **env)
{
  t_env		*tmp;
  t_env		*tempo;

  tmp = *env;
  while (tmp)
    {
      if (comp(tmp->line, ""))
	{
	  tempo = tmp->next;
	  if (tmp == *env && tempo)
	    tempo->previous = NULL;
	  if (tmp->previous == NULL && tmp->next == NULL)
	    *env = NULL;
	  else if (tmp->previous == NULL)
	    (*env) = (*env)->next;
	  xfree(tmp->line);
	  xfree(tmp);
	  tmp = tempo;
	}
      else
	tmp = tmp->next;
    }
  return (*env);
}
