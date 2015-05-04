/*
** decoup_tree.c for 42sh in /home/lund/Dossier courant/42sh/func/termcap
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Sun May 13 12:15:10 2012 florian dewulf
** Last update Wed May 16 23:46:47 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

static int	add_to_decoup(t_list **list, t_tree *ptr)
{
  t_list	*elem;
  t_list	*tmp;

  tmp = *list;
  if ((elem = malloc(sizeof(t_list))) == NULL)
    return (my_puterror_int(EXIT_MALLOC));
  elem->part = ptr;
  elem->prev = NULL;
  elem->next = NULL;
  if (tmp == NULL)
    *list = elem;
  else
    {
      while (tmp && tmp->next != NULL)
	tmp = tmp->next;
      tmp->next = elem;
      elem->prev = tmp;
    }
  return (0);
}

static void	remove_maille(t_tree **to_suppr)
{
  t_tree	*before;
  t_tree	*ptr;

  ptr = *to_suppr;
  *to_suppr = (*to_suppr)->right;
  before = ptr->left;
  if (before)
    before->right = NULL;
  xfree(ptr);
  if (*to_suppr)
    (*to_suppr)->left = NULL;
}

static t_list	*frag_tree(t_tree *tree)
{
  t_list	*list;
  t_tree	*begin;
  t_tree	*end;

  end = tree;
  list = NULL;
  while (end)
    {
      begin = end;
      while (end && end->type != PT)
	end = end->right;
      if (add_to_decoup(&list, begin) == -1)
	return (NULL);
      if (end)
	remove_maille(&end);
    }
  return (list);
}

static t_list	*all_is_list(t_tree *tree)
{
  t_list	*list;

  list = malloc(sizeof(t_list));
  if (list == NULL)
    return (my_puterror_null(EXIT_MALLOC));
  list->part = tree;
  list->next = NULL;
  return (list);
}

t_list		*decoup_tree(t_tree *tree)
{
  t_list	*list;
  t_tree	*tmp;

  tmp = tree;
  while (tmp && tmp->type != PT)
    tmp = tmp->right;
  if (!tmp)
    list = all_is_list(tree);
  else
    list = frag_tree(tree);
  return (list);
}
