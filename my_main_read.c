/*
** my_main_read.c for 42sh.h in /home/lund/Dossier courant/42sh/func/termcap
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Mon May  7 10:15:15 2012 florian dewulf
** Last update Sun May 20 01:33:38 2012 kevin lansel
*/

#include		<stdlib.h>
#include		<glob.h>
#include		<unistd.h>
#include		<sys/ioctl.h>
#include		<string.h>
#include		"42sh.h"

int			*init_curs(struct winsize *);

void			put_caractere(int *curs, char *buffer, char letter)
{
  char			*cap;

  cap = NULL;
  if (letter == '')
    {
      cap = xtgetstr_exe(cap, "cl");
      curs[0] = strlen(buffer);
      my_putstr(g_prompt);
      my_putstr(buffer);
    }
  else if (letter != '\t' && (letter >= ' ' && letter <= '~'))
    {
      my_putchar(letter);
      buffer[(curs[0])++] = letter;
      buffer[curs[0]] = '\0';
    }
}

static int		my_reduc_read(int *curs, char *buffer, char *carac,
				      t_history **history)
{
  if (my_strlen(carac) == 1 && carac[0] == '\n')
    return (0);
  else if (my_strlen(carac) == 1 && carac[0] == 4)
    return (-1);
  else if (strlen(carac) == 1 && carac[0] == 127 && strlen(buffer) >= 1 &&
	   curs[0] >= 1)
    erase_char(curs, buffer);
  else if (buffer[curs[0]] == '\0' && my_strlen(carac) == 1 &&
	   carac[0] != 127 && curs[0] < 511 && strlen(buffer) < 511 &&
	   carac[0] != '\t')
    put_caractere(curs, buffer, carac[0]);
  else if (buffer[curs[0]] != '\0' && my_strlen(carac) == 1 &&
	   carac[0] != 127 && strlen(buffer) < 511 && carac[0] != '\t')
    insere_char(buffer, curs, carac[0]);
  else
    *history = check_commande(buffer, curs, carac, history);
  return (1);
}

static void		check_tab_complet(int *curs, char *carac, int ret)
{
  carac[ret] = '\0';
  if (strlen(carac) == 1 && carac[0] == '\t' && curs[3] != 2)
    curs[3]++;
  else if (curs[3] != 2 && carac[0] != '\t')
    curs[3]--;
  if (curs[3] < 0)
    curs[3] = 0;
}

static void		cut_read(int *curs, char *carac)
{
  if (curs[0] + curs[2] == curs[1] && carac[0] >= ' ' && carac[0] < 127 &&
      !comp(carac, LEFT_TOUCH) && !comp(carac, RIGHT_TOUCH) &&
      !comp(carac, UP_TOUCH) && !comp(carac, DOWN_TOUCH))
    my_putchar('\n');
}

char			*my_read(t_history *history)
{
  char			carac[10];
  char			buffer[512];
  int			*curs;
  int			ret;
  struct winsize	win;

  ret = (buffer[0] = '\0') ? 1 : 1;
  if (ioctl(0, TIOCGWINSZ, &win) == -1 || (curs = init_curs(&win)) == NULL)
    return (my_strcpy(""));
  my_putstr(g_prompt);
  while (ret && ret != -1)
    {
      g_cursor = &(curs[0]);
      g_buffer = buffer;
      if ((ret = read(0, carac, 10)) <= 0)
	return (NULL);
      check_tab_complet(curs, carac, ret);
      if (ioctl(0, TIOCGWINSZ, &win) == -1)
	return (NULL);
      curs[1] = win.ws_col;
      ret = my_reduc_read(curs, buffer, carac, &history);
      cut_read(curs, carac);
    }
  put_end_word(curs, buffer);
  return ((ret == -1) ? NULL : my_strcpy(buffer));
}
