/*
** exec.c for 42sh in /home/seth/Desktop/42sh
** 
** Made by kevin lansel
** Login   <lansel_k@epitech.net>
** 
** Started on  Wed May  9 12:37:24 2012 kevin lansel
** Last update Sun May 20 02:15:00 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

static t_tree	*end_tree(t_tree *ptr)
{
  while (ptr->left != NULL)
    ptr = ptr->left;
  return (ptr);
}

static int	reduc_and(t_tree *tmp, int *hard, t_env *env, int *previous)
{
  int		ret;

  if ((ret = move_hard_tree_left(tmp, env)) == 0)
    {
      if ((ret = move_hard_tree_right(tmp, env)) == -2)
	return (-2);
      else if (ret == -1 && tmp->prev && tmp->prev->type == OR)
	*previous = 0;
      else if (ret == -1)
	*previous = -1;
      else if (ret == 0 && tmp->prev && tmp->prev->type == OR)
	*previous = -1;
    }
  else if (ret == -2)
    return (-2);
  else
    *previous = -1;
  (*hard)++;
  return (0);
}

static int	reduc_or(t_tree *tmp, int *hard, t_env *env, int *previous)
{
  int		ret;

  if (tmp->left->type == AND || (ret = move_hard_tree_left(tmp, env)) == -1)
    {
      if ((ret = move_hard_tree_right(tmp, env)) == -2)
	return (-2);
      else if (ret == -1)
	*previous = -1;
    }
  else if (ret == -2)
    return (-2);
  else
    *previous = 0;
  (*hard)++;
  return (0);
}

static int	work_exec(t_tree *tmp, int hard, t_env *env, int nb)
{
  static int	prev = 0;
  int		ret;

  if (nb == 1)
    return (prev = 0);
  if (tmp->type == AND && prev == 0)
    {
      ret = reduc_and(tmp, &hard, env, &prev);
      if (ret == -2)
	return (-2);
    }
  else if (tmp->type == OR && prev == 0)
    {
      ret = reduc_or(tmp, &hard, env, &prev);
      if (ret == -2)
	return (-2);
    }
  else if ((tmp->type == OR && prev == -1) ||
	   (tmp->type != OR && tmp->type != AND))
    prev = 0;
  return (hard);
}

int		exec(t_tree **tree, t_env *env)
{
  t_tree	*ptr;
  t_tree	*tmp;
  int		hard;

  ptr = (ptr = (*tree)) ? end_tree(ptr) : end_tree(ptr);
  hard = (tmp = ptr) ? 0 : 0;
  while (tmp)
    {
      if ((hard = work_exec(tmp, hard, env, 0)) == -2)
	return (-2);
      tmp = tmp->prev;
    }
  if (!tmp)
    work_exec(tmp, hard, env, 1);
  if (hard == 0)
    {
      ptr = *tree;
      if (ptr->type == COM)
	return (exe_simple(ptr->exp, env));
      else if (ptr->type == REDIR)
	return (check_redir2(ptr->exp, env, NULL));
      else
	return (multipipe(ptr, env));
    }
  return (0);
}
