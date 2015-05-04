/*
** lexer.c for 42sh in /home/lund/Dossier courant/42sh/func/termcap
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Sat May 12 18:23:16 2012 florian dewulf
** Last update Tue May 22 22:11:06 2012 florian dewulf
*/

#include		<stdlib.h>
#include		"42sh.h"

static int		cut_lexer(t_tree *list, t_env *env, t_alias *alias)
{
  t_tree		*list_tmp;
  t_list		*main_list;

  if (!last_check(list))
    return (0);
  modif_list(&list);
  list_tmp = list;
  while (list_tmp && alias)
    {
      list_tmp->exp = replace_string(alias, list_tmp->exp, env);
      list_tmp = list_tmp->right;
    }
  main_list = decoup_tree(list);
  return (parser(main_list, env));
}

int			lexer(char *str, t_env *env, t_alias *alias)
{
  t_tree		*list;

  while (g_histo && g_histo->prev)
    g_histo = g_histo->prev;
  str = order_com(str);
  if (str == NULL)
    return (-1);
  list = line_to_list(str);
  if (check_list(&list) && (group_redir(list) != -1) && check_valid_redir(list))
    return (cut_lexer(list, env, alias));
  else
    {
      my_putstr("Erreur syntaxe\n");
      return (-1);
    }
  return (0);
}
