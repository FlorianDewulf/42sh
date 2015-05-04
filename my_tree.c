/*
** my_tree.c for 42sh in /home/seth/Desktop/42sh
** 
** Made by kevin lansel
** Login   <lansel_k@epitech.net>
** 
** Started on  Fri May  4 13:29:22 2012 kevin lansel
** Last update Fri May 18 00:40:38 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

static void	check_tree_right(t_tree *memo, t_tree *ptr, int n)
{
  t_tree	*tree;

  tree = ptr;
  while (tree && tree->prio != n - 1)
    {
      if (tree->prio == n)
	{
	  add_to_right(&memo, tree);
	  recurse_tree(memo, tree, n + 1);
	  return;
	}
      tree = tree->right;
    }
  return;
}

static void    	check_tree_left(t_tree *memo, t_tree *ptr, int n)
{
  t_tree	*tree;

  tree = ptr;
  while (tree && tree->prio != n - 1)
    {
      if (tree->prio == n)
	{
	  add_to_left(&memo, tree);
	  recurse_tree(memo, tree, n + 1);
	  return;
	}
      tree = tree->left;
    }
  return;
}

void		recurse_tree(t_tree *memo, t_tree *ptr, int n)
{
  if (ptr != NULL)
    {
      check_tree_right(memo, ptr->right, n);
      check_tree_left(memo, ptr->left, n);
    }
}

static t_tree	*make_tree(t_tree *list)
{
  t_tree	*tree;
  t_tree	*ptr;

  ptr = list;
  while (ptr != NULL && ptr->prio != 1)
    ptr = ptr->right;
  tree = init_new_elem(ptr);
  recurse_tree(tree, ptr, ptr->prio + 1);
  return (tree);
}

t_tree		*my_tree(t_tree *list)
{
  t_tree	*ptr;
  int		tm;
  t_tree	*tree;

  check_first_prio(&list);
  tm = 1;
  while (check_list_prio(&list))
    {
      ptr = list;
      while (ptr != NULL)
	{
	  if (ptr->prio == tm)
	    {
	      check_right((&ptr->right), (tm + 1));
	      check_left((&ptr->left), (tm + 1));
	    }
	  ptr = ptr->right;
	}
      tm++;
    }
  tree = make_tree(list);
  free_list(list);
  return (tree);
}
