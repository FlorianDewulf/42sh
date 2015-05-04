/*
** move_tree.c for 42sh in /home/seth/Desktop/42sh
** 
** Made by kevin lansel
** Login   <lansel_k@epitech.net>
** 
** Started on  Thu May 10 18:57:14 2012 kevin lansel
** Last update Wed May 16 22:55:47 2012 florian dewulf
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	"42sh.h"

int		move_hard_tree_left(t_tree *tmp, t_env *env)
{
  t_tree	*mv;

  mv = tmp->left;
  if (mv && mv->type == REDIR)
    return (check_redir2(mv->exp, env, NULL));
  else if (mv && mv->type == COM)
    return (exe_simple(mv->exp, env));
  else if (mv && mv->type == PIPE)
    return (multipipe(mv, env));
  return (0);
}

int		move_hard_tree_right(t_tree *tmp, t_env *env)
{
  t_tree	*mv;

  mv = tmp->right;
  if (mv && mv->type == REDIR)
    return (check_redir2(mv->exp, env, NULL));
  else if (mv && mv->type == COM)
    return (exe_simple(mv->exp, env));
  else if (mv && mv->type == PIPE)
    return (multipipe(mv, env));
  return (0);
}
