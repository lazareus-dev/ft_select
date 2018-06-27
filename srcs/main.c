/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 10:55:55 by tle-coza     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/27 16:25:27 by tle-coza    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <termcap.h>
#include <signal.h>
#include <sys/ioctl.h>
#include "../includes/ft_select.h"
#include "../includes/sel_select.h"
#include "../includes/sel_display.h"
#include "../includes/sel_lst.h"

void	move_right(void)
{
	t_select	*select;
	char		*move;

	select = get_select();
	move = tgetstr("nd", NULL);
	tputs(move, 0, ft_putchar_term);
}

void	move_left(void)
{
	t_select	*select;
	char		*move;

	select = get_select();
	move = tgetstr("le", NULL);
	tputs(move, 0, ft_putchar_term);
}

void	keys(char buffer[])
{
		if (buffer[2] == 'A')
			ft_putstr("^");
		else if (buffer[2] == 'B')
			ft_putstr("v");
		else if (buffer[2] == 'C')
			move_right();
		else if (buffer[2] == 'D')
			move_left();
		else if (buffer[2] == '3')
			ft_putendl("Delete");
		else if (buffer[2] == 'H')
			ft_putendl("Home");
		else if (buffer[2] == 'F')
			ft_putendl("End");
		else
			ft_putstr(&buffer[1]);
}

int     voir_touche()
{
	char     buffer[4];

	while (1)
	{
		ft_bzero(buffer, 4);
		read(0, buffer, 4);
		if (buffer[0] == 27)
			keys(buffer);
		else if (buffer[0] == 4)
		{
			printf("Ctlr+d, on quitte !\n");
			return (0);
		}
		else if (buffer[0] == '\n')
			return (0);
		else if (buffer[0] == ' ')
			ft_putendl("Select");
		else if (buffer[0] == 127)
			ft_putendl("Delete");
	}
	return (0);
}

int		*set_winsize(void)
{
	t_select *select;

	select = get_select();
	ioctl(0, TIOCGWINSZ, &(select->win));
	return (0);
}

void handle_winch(int sig)
{
	t_select	*select;
	
	signal(SIGWINCH, SIG_IGN);
	set_winsize();
	select = get_select();
	dprintf(1, "col: %u, row: %u\n", select->win.ws_col, select->win.ws_row);
	signal(SIGWINCH, handle_winch);
}

void	restore_term(t_select *select)
{
	ft_putstr(RESET);
	tcsetattr(0, TCSADRAIN, &(select->orig_termios));
	tputs(tgetstr("te", NULL), 0, ft_putchar_term);
	ft_putstr("Cleared and Reset\n");
}

void	clear_select(void)
{
	t_select	*select;
	char		*cmd;

	select = get_select();
	free_arglst(select->arglst);
	ft_strdel(&(select->buff));
	free(select);
}

int		sel_loop(void)
{
	while (101)
	{
	}
}

void	sigint_handler(int sig)
{
	t_select	*select;

	select = get_select();
	if (sig == SIGTSTP)
	{
		signal(SIGTSTP, SIG_DFL);
		ioctl(0, TIOCSTI, "\x1a");
		restore_term(select);
	}
	else if (sig == SIGCONT)
	{
		ft_putstr(GREEN);
		signal(SIGTSTP, sigint_handler);
		tcsetattr(0, TCSADRAIN, &(select->term));
	}
	else
	{
		clear_select();
		restore_term(select);
		exit(0);
	}
}

void	sig_handlers(void)
{
	signal(SIGWINCH, handle_winch);
	signal(SIGINT, sigint_handler);
	signal(SIGTERM, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	signal(SIGCONT, sigint_handler);
	signal(SIGTSTP, sigint_handler);
//	if ((signal(SIGSEGV, sigint_handler) == SIG_ERR))
//		ft_putendl("SIGSEGV error");
}

void	init_ft_select(void)
{
	char		*cmd;

	ft_putstr(GREEN);
	cmd = tgetstr("ti", NULL);
	tputs(cmd, 0, ft_putchar_term);
}

int		main(int ac, char **av)
{
	t_select	*select;
	int			ret;

	if (ac == 1)
		return (0);
	sig_handlers();
	select = get_select();
	init_arglst(select->arglst, ac, av);
	init_ft_select();
	display_list(select->arglst);
	voir_touche();
//	sel_loop();
	restore_term(select);
	echo_result();
	clear_select();
	return (0);
}
