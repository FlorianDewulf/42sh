/*
** elem_tree.c for 42sh.h in /home/lund/Dossier courant/42sh/func/termcap
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Tue May  8 23:31:38 2012 florian dewulf
** Last update Tue May  8 23:32:22 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

t_tree		*init_new_elem(t_tree *ptr)
{
  t_tree	*elem;

  elem = xmalloc(sizeof(t_tree));
  elem->type = ptr->type;
  elem->exp = my_strcpy(ptr->exp);
  elem->prio = ptr->prio;
  elem->right = NULL;
  elem->left = NULL;
  elem->prev = NULL;
  return (elem);
}

void		add_to_right(t_tree **tree, t_tree *elem)
{
  t_tree	*ptr;

  ptr = *tree;
  if (*tree != NULL)
    {
      elem = init_new_elem(elem);
      ptr->right = elem;
      elem->prev = ptr;
    }
  *tree = elem;
}

void		add_to_left(t_tree **tree, t_tree *elem)
{
  t_tree	*ptr;

  ptr = *tree;
  if (*tree != NULL)
    {
      elem = init_new_elem(elem);
      ptr->left = elem;
      elem->prev = ptr;
    }
  *tree = elem;
}
