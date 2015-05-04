/*
** group_redir.c for 42sh in /home/lund/Dossier courant/42sh/func/termcap
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Wed May  9 19:34:18 2012 florian dewulf
** Last update Wed May 16 17:50:15 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

static char	*concate_chain(t_tree *begin, t_tree *end)
{
  char		*tempo;
  char		*str;
  t_tree	*list;

  list = begin;
  str = list->exp;
  while (list->right != end)
    {
      if ((tempo = concate(str, " ")) == NULL)
	return (NULL);
      list = list->right;
      xfree(str);
      if ((str = concate(tempo, list->exp)) == NULL)
	return (NULL);
      xfree(tempo);
    }
  return ((str = epur_space(str)));
}

static void	free_maille(t_tree *ptr, t_tree *end)
{
  t_tree	*tmp;

  while (ptr != end)
    {
      tmp = ptr->right;
      xfree(ptr);
      ptr = tmp;
    }
}

static int	reduc_else(t_tree **tmp)
{
  char		*str;
  t_tree	*begin;
  t_tree	*end;

  begin = (*tmp)->left;
  while ((*tmp) && ((*tmp)->type == REDIR || (*tmp)->type == COM))
    (*tmp) = (*tmp)->right;
  end = (*tmp);
  if ((str = concate_chain(begin, end)) == NULL)
    return  (-1);
  free_maille(begin->right, end);
  begin->exp = str;
  begin->type = REDIR;
  begin->right = end;
  if (end)
    end->left = begin;
  return (0);
}

int		group_redir(t_tree *list)
{
  t_tree	*tmp;

  tmp = list;
  while (tmp)
    {
      while (tmp && tmp->type != REDIR)
	tmp = tmp->right;
      if (!tmp)
	return (0);
      else
	if (reduc_else(&tmp) == -1)
	  return (-1);
    }
  return (0);
}
