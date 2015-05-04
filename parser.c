/*
** parser.c for 42sh in /home/lund/Dossier courant/42sh/func/termcap/arbre
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Sun May 13 18:53:36 2012 florian dewulf
** Last update Tue May 22 19:42:26 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

int		parser(t_list *list, t_env *env)
{
  t_list	*tmplist;
  t_tree	*tmp;

  tmplist = list;
  while (tmplist)
    {
      tmplist->part = my_tree(tmplist->part);
      tmplist = tmplist->next;
    }
  tmplist = list;
  while (tmplist)
    {
      tmp = tmplist->part;
      if (exec(&tmp, env) == -2)
	return (-2);
      tmplist = tmplist->next;
    }
  return (0);
}
