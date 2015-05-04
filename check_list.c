/*
** check_list.c for 42sh.h in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Wed May  2 15:34:56 2012 florian dewulf
** Last update Tue May 22 22:57:14 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

static int	check_list_bis(t_tree *ptr)
{
  int		i;
  t_tree	*tmp;

  i = 0;
  tmp = ptr;
  while (tmp)
    {
      if (((i % 2) == 0 && tmp->type != COM) ||
	  ((i % 2) == 1 && tmp->type == COM))
	return (-1);
      else if (tmp->type == PT)
	{
	  i = -1;
	  while (tmp->type == PT && tmp->right && tmp->right->type == PT)
	    tmp = tmp->right;
	}
      tmp = tmp->right;
      i++;
    }
  return (0);
}

int		check_list(t_tree **list)
{
  t_tree	*chain;

  chain = *list;
  if (check_list_bis(chain) == -1)
    return (0);
  if (chain)
    {
      while (chain->right)
	chain = chain->right;
      if (chain->type == COM)
	return (1);
      else if (chain->type == PT)
	{
	  chain->left->right = NULL;
	  xfree(chain->exp);
	  xfree(chain);
	  return (1);
	}
      else
	return (0);
    }
  return (0);
}
