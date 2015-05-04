/*
** termcap.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Thu May  3 13:47:45 2012 florian dewulf
** Last update Sat May 19 16:58:18 2012 kevin lansel
*/

#include		<curses.h>
#include		<term.h>
#include		<termios.h>
#include		<unistd.h>
#include		<stdlib.h>
#include		"42sh.h"

int			termcap_desinit(t_env *env)
{
  char			*bp;
  struct termios	t;
  t_env			*tmp;
  char			*name;

  bp = NULL;
  tmp = env;
  while (tmp && !compegal(tmp->line, "TERM"))
    tmp = tmp->next;
  if (!tmp)
    if ((name = my_strcpy("TERM=xterm")) == NULL)
      return (-1);
  if (tmp && (name = my_strcpy(tmp->line)) == NULL)
    return (-1);
  my_revstr(name);
  name[my_strlen(name) - 5] = '\0';
  my_revstr(name);
  if (tcgetattr(0, &t) == -1)
    return (-1);
  if (tgetent(bp, name) < 1)
    return (-1);
  xfree(name);
  t.c_lflag = 35387;
  tcsetattr(0, TCSANOW, &t);
  return (0);
}

static int		change_mode(struct termios *t)
{
  t->c_cc[VMIN] = 1;
  t->c_lflag &= (~ICANON & ~ECHO);
  if (tcsetattr(0, TCSANOW, t) == -1)
    return (-1);
  return (0);
}

int			init_termcap(t_env *env)
{
  char			*bp;
  struct termios	t;
  t_env			*tmp;

  bp = NULL;
  tmp = env;
  g_buffer = NULL;
  while (tmp && !compegal(tmp->line, "TERM"))
    tmp = tmp->next;
  if (!tmp)
    return (-1);
  if (tcgetattr(0, &t) == -1)
    return (-1);
  if (tgetent(bp, (&tmp->line[5])) < 1)
    return (-1);
  if (change_mode(&t) == -1)
    return (-1);
  return (1);
}
