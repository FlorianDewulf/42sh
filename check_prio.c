/*
** check_prio.c for 42sh in /home/seth/Desktop/42sh
** 
** Made by kevin lansel
** Login   <lansel_k@epitech.net>
** 
** Started on  Mon May  7 16:16:03 2012 kevin lansel
** Last update Tue May 15 11:10:57 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

t_tree		*end_list(t_tree **list)
{
  t_tree	*ptr;

  ptr = *list;
  while (ptr->right)
    ptr = ptr->right;
  return (ptr);
}

void		check_first_prio(t_tree **list)
{
  t_tree	*ptr;
  t_tree	*tmp;
  int		n;

  ptr = end_list(list);
  tmp = NULL;
  n = END;
  while (ptr)
    {
      if (ptr->type == AND || ptr->type == OR)
	{
	  n = ptr->type;
	  tmp = ptr;
	  tmp->prio = 1;
	  return;
	}
      else if (ptr->type < n)
	{
	  n = ptr->type;
	  tmp = ptr;
	}
      ptr = ptr->left;
    }
  if (tmp != NULL)
    tmp->prio = 1;
}

int		check_list_prio(t_tree **list)
{
  t_tree	*ptr;

  ptr = *list;
  while (ptr != NULL)
    {
      if (ptr->prio == 0)
	return (1);
      ptr = ptr->right;
    }
  return (0);
}

void		check_right(t_tree **list, int tm)
{
  t_tree	*ptr;
  t_tree	*tmp;
  int		n;

  ptr = *list;
  n = (tmp = NULL) ? END : END;
  if (ptr == NULL || (ptr && ptr->prio != 0))
    return;
  while (ptr && ptr->right != NULL && ptr->right->prio == 0)
    ptr = ptr->right;
  while (ptr != NULL && ptr->prio == 0)
    {
      if ((ptr->type == AND || ptr->type == OR) && ptr->prio == 0)
	{
	  ptr->prio = tm;
	  return;
	}
      else if (ptr->type < n && ptr->prio == 0)
	{
	  n = ptr->type;
	  tmp = ptr;
	}
      ptr = ptr->left;
    }
  (tmp != NULL && tmp->prio == 0) ? (tmp->prio = tm) : 1;
}

void		check_left(t_tree **list, int tm)
{
  t_tree	*ptr;
  t_tree	*tmp;
  int		n;

  ptr = *list;
  tmp = NULL;
  n = END;
  while (ptr != NULL && ptr->prio == 0)
    {
      if ((ptr->type == AND || ptr->type == OR) && ptr->prio == 0)
	{
	  ptr->prio = tm;
	  return;
	}
      else if (ptr->type < n && ptr->prio == 0)
	{
	  n = ptr->type;
	  tmp = ptr;
	}
      ptr = ptr->left;
    }
  if (tmp != NULL && tmp->prio == 0)
    tmp->prio = tm;
  return;
}
