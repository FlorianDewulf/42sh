/*
** last_check.c for 42sh in /home/lund/Dossier courant/42sh/func/termcap
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Sun May 13 15:14:37 2012 florian dewulf
** Last update Wed May 16 22:16:07 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

int		last_check(t_tree *tree)
{
  t_tree	*tmp;

  tmp = tree;
  while (tmp)
    {
      while (tmp && tmp->type != REDIR)
	tmp = tmp->right;
      if (tmp && tmp->right != NULL &&
	  (tmp->right->type == COM || tmp->right->type == PIPE) &&
	  tmp->right->type != PT)
	{
	  my_putstr("Ambiguous output redirect.\n");
	  return (0);
	}
      else if (tmp != NULL)
	tmp = tmp->right;
    }
  return (1);
}
