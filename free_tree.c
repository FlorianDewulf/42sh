/*
** free_tree.c for 42sh in /home/seth/42sh-2016-dewulf_f
** 
** Made by kevin lansel
** Login   <lansel_k@epitech.net>
** 
** Started on  Thu May 17 17:26:15 2012 kevin lansel
** Last update Tue May 22 21:39:12 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

static t_tree	*end_tree(t_tree **ptr)
{
  if (*ptr && (*ptr)->left)
    {
      while ((*ptr) && (*ptr)->left)
	(*ptr) = (*ptr)->left;
    }
  return (*ptr);
}

static void	free_left(t_tree **ptr)
{
  if ((*ptr) && (*ptr)->prev)
    {
      (*ptr) = (*ptr)->prev;
      if ((*ptr)->left)
	{
	  xfree((*ptr)->left->exp);
	  xfree((*ptr)->left);
	}
      if ((*ptr)->right && (*ptr)->type != AND && (*ptr)->type != OR)
	{
	  xfree((*ptr)->right->exp);
	  xfree((*ptr)->right);
	}
    }
}

static void	free_right(t_tree **ptr)
{
  t_tree	*tmp;
  t_tree	*tempo;

  tmp = (*ptr);
  tempo = *ptr;
  tempo = end_tree(&tempo);
  while (tempo != tmp)
    free_left(&tempo);
  *ptr = tempo;
}

void		free_tree(t_tree *tree)
{
  t_tree	*ptr;

  ptr = tree;
  ptr = end_tree(&ptr);
  while (ptr)
    {
      if (ptr && ptr->type != OR && ptr->type != AND && ptr->prev)
	free_left(&ptr);
      else if (ptr && (ptr->type == OR || ptr->type == AND))
	{
	  if (ptr->right != NULL)
	    free_right(&(ptr->right));
	}
      if (ptr->prev == NULL)
	{
	  xfree(ptr->exp);
	  xfree(ptr);
	  ptr = NULL;
	}
    }
}
