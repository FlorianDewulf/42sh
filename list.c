/*
** list.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Mon Apr 23 17:17:25 2012 florian dewulf
** Last update Wed May  9 19:04:46 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

static t_tree	*new_elem(char *str)
{
  t_tree	*elem;

  elem = xmalloc(sizeof(t_tree));
  elem->left = NULL;
  elem->right = NULL;
  elem->prev = NULL;
  elem->prio = 0;
  elem->type = check_type(str);
  elem->exp = str;
  return (elem);
}

void		add_elem(t_tree **list, char *str)
{
  t_tree	*tmp;
  t_tree	*elem;

  elem = new_elem(str);
  if (*list == NULL)
    *list = elem;
  else
    {
      tmp = *list;
      while (tmp->right)
	tmp = tmp->right;
      tmp->right = elem;
      elem->left = tmp;
    }
}
