/*
** free.c for 42sh.h in /home/lund/Dossier courant/42sh/func/termcap
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Fri May 11 18:41:42 2012 florian dewulf
** Last update Fri May 18 14:33:46 2012 kevin lansel
*/

#include	<stdlib.h>
#include	"42sh.h"

void		free_env(t_env *env)
{
  t_env		*tmp;

  tmp = env;
  if (!tmp)
    return;
  while (tmp && tmp->next != NULL)
    tmp = tmp->next;
  while (tmp)
    {
      xfree(tmp->line);
      if (tmp->previous == NULL)
	{
	  xfree(tmp);
	  tmp = NULL;
	}
      else
	tmp = tmp->previous;
      if (tmp)
	xfree(tmp->next);
    }
  env = NULL;
}

void		free_history(t_history *histo)
{
  t_history	*tmp;

  tmp = histo;
  if (!tmp)
    return;
  while (tmp && tmp->next != NULL)
    tmp = tmp->next;
  while (tmp)
    {
      xfree(tmp->line);
      if (tmp->prev == NULL)
	{
	  free(tmp);
	  tmp = NULL;
	}
      else
	tmp = tmp->prev;
      if (tmp)
	xfree(tmp->next);
    }
  histo = NULL;
}

void		free_alias(t_alias *alias)
{
  t_alias	*tmp;
  t_alias	*tempo;

  tmp = alias;
  while (tmp)
    {
      tempo = tmp->next;
      xfree(tmp->pattern);
      xfree(tmp->exp);
      xfree(tmp);
      tmp = tempo;
    }
}

void		free_list(t_tree *list)
{
  t_tree	*tmp;
  t_tree	*tempo;

  tmp = list;
  tempo = tmp;
  while (tmp)
    {
      tempo = tmp->right;
      xfree(tmp->exp);
      xfree(tmp);
      tmp = tempo;
    }
}
