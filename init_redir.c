/*
** init_redir.c for 42 in /home/david/Projet/42sh/exec/redir_droite
** 
** Made by david blervaque
** Login   <blerva_d@epitech.net>
** 
** Started on  Wed May  2 15:14:16 2012 david blervaque
** Last update Thu May 17 11:46:13 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

t_redir		*init_redir()
{
  t_redir	*red;

  red = xmalloc(SIZE_REDIR * sizeof(t_redir));
  red[0].redir = "*>";
  red[0].func = &init_srr;
  red[1].redir = "*>>";
  red[1].func = &init_drr;
  red[2].redir = "<";
  red[2].func = &init_slr;
  red[3].redir = "<<";
  red[3].func = &init_dlr;
  return (red);
}

t_redir		*init_redir_2()
{
  t_redir	*red;

  red = xmalloc(2 * sizeof(t_redir));
  red[0].redir = "*>";
  red[0].func = &init_srr2;
  red[1].redir = "*>>";
  red[1].func = &init_drr2;
  return (red);
}
