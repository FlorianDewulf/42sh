/*
** modif_list.c for 42sh in /home/lund/Dossier courant/42sh/v1.0
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Thu May 17 11:13:27 2012 florian dewulf
** Last update Thu May 17 13:14:53 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

static void	check_around_redir(t_tree **list)
{
  t_tree	*repere;
  t_tree	*tmp;

  tmp = *list;
  if (tmp->left && tmp->left->type == PIPE)
    {
      repere = tmp;
      while (tmp->left && (tmp->left->type == PIPE || tmp->left->type == COM))
	tmp = tmp->left;
      if (tmp->left == NULL)
	{
	  *list = repere;
	  repere->left->right = NULL;
	  repere->left = NULL;
	  free_list(tmp);
	}
      else
	{
	  tmp->left->right = repere;
	  repere->left->right = NULL;
	  repere->left = tmp->left;
	  free_list(tmp);
	}
    }
}

static int	check_type_redir(char *str)
{
  int		curs;

  curs = -1;
  while (str[++curs])
    if (str[curs] == '<')
      return (1);
  return (0);
}

void		modif_list(t_tree **list)
{
  t_tree	*tmp;
  t_tree	*tempo;

  tmp = *list;
  while (tmp)
    {
      while (tmp && tmp->type != REDIR)
	tmp = tmp->right;
      if (tmp == NULL)
	return;
      else if (tmp != *list && check_type_redir(tmp->exp))
	check_around_redir(&tmp);
      if (tmp->right == NULL)
	tempo = tmp;
      tmp = tmp->right;
    }
  tmp = tempo;
  while (tmp->left)
    tmp = tmp->left;
  *list = tmp;
}
